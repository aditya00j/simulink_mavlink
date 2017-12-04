function create_sfun_encode(filename, sys_id, comp_id)
% CREATE_SFUN_ENCODE: Create and compile the S-function to encode a MAVLink
% message
%
% Inputs:
%   filename: string containing the MAVLink message header file
%   sys_id: MAVLink SYSID to be used for Simulink (default 100)
%   comp_id: MAVLink COMPID to be used for Simulink (default 200)
%
% Output:
%   This function creates the Simulink bus, the s-function header file, the
%   s-function source file, and finally compiles the s-function.
%
%Part of the Simulink MAVLink package.
%(c) Aditya Joshi, November 2017


%% Create header file

disp(' ')
disp(['*** Running create_sfun_encode for ' filename ':'])

if nargin < 2, sys_id = 100; end
if nargin < 3, comp_id = 200; end
    
mavlink_msg_name = create_sfun_header(filename);


%% Create cpp file

output_filename = ['sfun_encode_msg_' mavlink_msg_name];
fprintf(['Creating the output file ' output_filename '.cpp ... ']);

fin = fopen('sfun_encode_msg_template.cpp','r');
fout = fopen([output_filename '.cpp'],'w');

% Write header
fprintf(fout,'%s\n','/*');
fprintf(fout,'%s\n','DO NOT EDIT.');
fprintf(fout,'%s\n',['This file was automatically created by the Matlab function ''create_sfun_encode'' on ' datestr(now)]);
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
                fprintf(fout,'%s\n',['#define S_FUNCTION_NAME  sfun_encode_msg_' mavlink_msg_name]);
                
            case 2
                fprintf(fout,'%s\n',['#define SYS_ID ' num2str(sys_id)]);
                
            case 3
                fprintf(fout,'%s\n',['#define COMP_ID ' num2str(comp_id)]);
                
            case 4
                fprintf(fout,'%s\n',['#include "include/sfun_mavlink_msg_' mavlink_msg_name '.h"']);
                
            case 5
                fprintf(fout,'\t%s\n',['ssRegisterTypeFromNamedObject(S, BUS_NAME_' upper(mavlink_msg_name) ', &BusType);']);
                
            case 6
                fprintf(fout,'\t%s\n',['ssSetOutputPortWidth(S, 0, ENCODED_LEN_' upper(mavlink_msg_name) ');']);
                
            case 7
                fprintf(fout,'\t%s\n',['int_T *busInfo = (int_T *) malloc(2*NFIELDS_BUS_' upper(mavlink_msg_name) '*sizeof(int_T));']);
                
            case 8
                fprintf(fout,'\t%s\n',['encode_businfo_' mavlink_msg_name '(S, busInfo, 0);']);
                
            case 9
                fprintf(fout,'\t%s\n',['encode_vector_' mavlink_msg_name '(uvec, busInfo, yvec, 0);']);    
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
eval(['mex ' output_filename '.cpp']);

movefile([output_filename '.*'],'sfunctions');
disp('S-function source and compiled files are in the folder ''sfunctions''')

disp('***')

