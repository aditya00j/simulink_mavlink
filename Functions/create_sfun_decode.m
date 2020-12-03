function create_sfun_decode(filenames, nmax, sys_id, comp_id)
% CREATE_SFUN_DECODE: Create and compile the S-function to decode MAVLink
% messages from an incoming MAVLink stream
%
% Inputs:
%   filenames: cell array of strings containing the MAVLink message header
%              files for messages to be decoded.
%   nmax: maximum number of messages received in one iteration. This can be
%         determined from the buffer size of the receiving channel.
%         (default 1)
%   sys_id: MAVLink SYSID to be used for Simulink (default 100)
%   comp_id: MAVLink COMPID to be used for Simulink (default 200)
%
% Output:
%   This function creates the Simulink buses, the s-function header files,
%   the s-function source file, and finally compiles the s-function.
%
%Part of the Simulink MAVLink package.
%(c) Aditya Joshi, November 2017

if ~iscell(filenames), filenames = {filenames}; end

disp('--')
disp('Creating decoder s-function:')

if nargin < 2, nmax = 1; end
if nargin < 3, sys_id = 100; end
if nargin < 4, comp_id = 200; end


%% Create message header files

mavlink_msg_names = cell(length(filenames));
for i = 1:length(filenames)
    mavlink_msg_names{i} = create_sfun_header(filenames{i});
end


%% Create header file

fprintf('Writing the decoder s-function header file... ')

header_filename = 'Generated/sfun_decode_mavlink.h';

fid = fopen(header_filename, 'w');

% Write header
fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','DO NOT EDIT.');
fprintf(fid,'%s\n',['This file was automatically created by the Matlab function ''create_sfun_decode'' on ' datestr(now)]);
fprintf(fid,'%s\n','as part of Simulink MAVLink library.');
fprintf(fid,'%s\n','*/');
fprintf(fid,'%s\n','');

% Include message headers
for i = 1:length(filenames)
    fprintf(fid,'%s\n',['#include "sfun_mavlink_msg_' mavlink_msg_names{i} '.h"']);
end

% Define NFIELDS_OUTPUT_BUS
fprintf(fid,'%s\n','');
fprintf(fid,'%s',['#define NFIELDS_OUTPUT_BUS (NFIELDS_BUS_' upper(mavlink_msg_names{1})]);
if length(filenames) > 1
    for i = 2:length(filenames)
        fprintf(fid,'%s',[' + NFIELDS_BUS_' upper(mavlink_msg_names{i})]);
    end
end
fprintf(fid,'%s\n',')');

% calculate bus offsets for each message
fprintf(fid,'%s\n','');
fprintf(fid,'%s\n',['#define OFFSET_' upper(mavlink_msg_names{1}) ' 0']);
if length(filenames) > 1
    for i = 2:length(filenames)
        lin = ['#define OFFSET_' upper(mavlink_msg_names{i}) ' 2*('];
        for j = i-1:-1:1
            lin = [lin 'NFIELDS_BUS_' upper(mavlink_msg_names{j}) '+'];
        end
        lin(end) = ')';
        fprintf(fid,'%s\n',lin);
    end
end

% Write decode_mavlink_msg function
fprintf(fid,'%s\n','');
fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','Decode the incoming MAVLink message');
fprintf(fid,'%s\n','*/');
fprintf(fid,'%s\n','static inline void decode_mavlink_msg (SimStruct *S, const mavlink_message_t *msg)');
fprintf(fid,'%s\n','{');
fprintf(fid,'\t%s\n','int_T *busInfo = (int_T *) ssGetUserData(S);');
fprintf(fid,'%s\n','');
fprintf(fid,'\t%s\n','real_T  *ystatus = ssGetOutputPortRealSignal(S, 0);');
fprintf(fid,'%s\n','');


for i = 1:length(filenames)
    fprintf(fid,'\t%s\n',['char* yvec' num2str(i) ' = (char *) ssGetOutputPortRealSignal(S, ' num2str(i) ');']);
end
fprintf(fid,'\t%s\n','switch (msg->msgid) {');
for i = 1:length(filenames)
    fprintf(fid,'%s\n','');
    fprintf(fid,'\t\t%s\n',['case MAVLINK_MSG_ID_' upper(mavlink_msg_names{i}) ':']);
    fprintf(fid,'\t\t\t%s\n',['ystatus[' num2str(i-1) '] = 1;']);
    fprintf(fid,'\t\t\t%s\n',['decode_msg_' mavlink_msg_names{i} '(msg, busInfo, yvec' num2str(i) ', OFFSET_' upper(mavlink_msg_names{i}) ');']); 
    fprintf(fid,'\t\t\t%s\n','break;');
end
fprintf(fid,'\t%s\n','}');
fprintf(fid,'%s\n','}');


fclose(fid);
disp('done')


%% Create cpp file

output_filename = 'Generated/sfun_decode_mavlink';
fprintf(['Writing source file ' output_filename '.cpp ... ']);

fin = fopen('sfun_decode_mavlink_template.cpp','r');
fout = fopen([output_filename '.cpp'],'w');

% Write header
fprintf(fout,'%s\n','/*');
fprintf(fout,'%s\n','DO NOT EDIT.');
fprintf(fout,'%s\n',['This file was automatically created by the Matlab function ''create_sfun_decode'' on ' datestr(now)]);
fprintf(fout,'%s\n','as part of Simulink MAVLink library.');
fprintf(fout,'%s\n','*/');

% Skip header from template file
lin = fgetl(fin);
while ~contains(lin,'<BEGIN>')
    lin = fgetl(fin);
end
lin = fgetl(fin);

% Start writing editable lines
while ~contains(lin,'<END>')
    
    if contains(lin,'<EDIT>')
        idx = regexp(lin,'<(\d*)>','match');
        idx = idx{1};
        idx = str2double(erase(idx,{'<','>'}));
        
        switch idx
            case 1
                % define SYS_ID
                fprintf(fout,'%s\n',['#define SYS_ID ' num2str(sys_id)]);
                
            case 2
                % define COMP_ID
                fprintf(fout,'%s\n',['#define COMP_ID ' num2str(comp_id)]);
                
            case 3
                % include mavlink.h file
                mavlink_h = strcat(fileparts(filenames{1}), filesep, 'mavlink.h');
                fprintf(fout,'%s\n',['#include "' mavlink_h '"']);
                
            case 4
                % include message header file
                fprintf(fout,'%s\n', '#include "sfun_decode_mavlink.h"');
                
            case 5
                % configure input port length
                fprintf(fout,'%s\n', ['ssSetInputPortVectorDimension(S, 0, ' num2str(nmax) '*MAVLINK_MAX_PACKET_LEN);']);
                
            case 6
                % configure output ports
                fprintf(fout,'\t%s\n',['if (!ssSetNumOutputPorts(S, ' num2str(i+1) ')) return;']);
                fprintf(fout,'%s\n','');
                fprintf(fout,'\t%s\n',['ssSetOutputPortWidth(S, 0, ' num2str(i) ');']);
                fprintf(fout,'%s\n','');
                fprintf(fout,'\t%s\n','#if defined(MATLAB_MEX_FILE)');
                fprintf(fout,'\t%s\n','if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY)');
                fprintf(fout,'\t%s\n','{');
                for i = 1:length(filenames)
                    fprintf(fout,'\t\t%s\n',['DTypeId dataTypeIdReg' num2str(i) ';']);
                    fprintf(fout,'\t\t%s\n',['ssRegisterTypeFromNamedObject(S, BUS_NAME_' upper(mavlink_msg_names{i}) ', &dataTypeIdReg' num2str(i) ');']);
                    fprintf(fout,'\t\t%s\n',['if (dataTypeIdReg' num2str(i) ' == INVALID_DTYPE_ID) return;']);
                    fprintf(fout,'\t\t%s\n',['ssSetOutputPortDataType(S, ' num2str(i) ', dataTypeIdReg' num2str(i) ');']);
                    fprintf(fout,'%s\n','');
                end
                fprintf(fout,'\t%s\n','}');
                fprintf(fout,'\t%s\n','#endif');
                
                
                fprintf(fout,'%s\n','');
                for i = 1:length(filenames)
                    fprintf(fout,'\t%s\n',['ssSetBusOutputObjectName(S, ' num2str(i) ', (void *) BUS_NAME_' upper(mavlink_msg_names{i}) ');']);
                end
                                
                fprintf(fout,'%s\n','');
                for i = 1:length(filenames)
                    fprintf(fout,'\t%s\n',['ssSetOutputPortWidth(S, ' num2str(i) ', 1);']);
                end
                                
                fprintf(fout,'%s\n','');
                for i = 1:length(filenames)
                    fprintf(fout,'\t%s\n',['ssSetBusOutputAsStruct(S, ' num2str(i) ', 1);']);
                end
                                
                fprintf(fout,'%s\n','');
                for i = 1:length(filenames)
                    fprintf(fout,'\t%s\n',['ssSetOutputPortBusMode(S, ' num2str(i) ', SL_BUS_MODE);']);
                end
                
            case 7
                % encode_businfo for each message
                for i = 1:length(filenames)
                    fprintf(fout,'\t%s\n',['encode_businfo_' mavlink_msg_names{i} '(S, busInfo, OFFSET_' upper(mavlink_msg_names{i}) ');']);
                end
                
            otherwise
                error(['Unknown <EDIT> tag: ' num2str(idx)]);
            
        end
        
    else
        fprintf(fout,'%s\n',lin);
    end
    
    lin = fgetl(fin);
end

fclose(fin);
fclose(fout);
disp('done');


%% Compile cpp file

disp('Compiling the s-function...')
eval('cd Generated')
eval('mex sfun_decode_mavlink.cpp');
eval('cd ..')

disp('Finished, compiled s-function is in the folder ''Generated''')
disp('--')