function mavlink_msg_name = create_sfun_header(filename)
% CREATE_SFUN_HEADER: Create the message header files for s-functions in Simulink MAVLink
%
% Inputs:
%   mavlink_msg_name: string containing the name of the mavlink message. In the
%                     standard naming convention, everythin after the "mavlink_msg_"
%                     in the name of the mavlink header file is considered the
%                     message name. e.g. if the header file is "mavlink_msg_altitude",
%                     the message name is "altitude".
%   simulink_bus: the Simulink bus object corresponding to this message. This bus
%                     is created by the function "create_bus_from_mavlink_header"
%
% Output: the function creates the .h header file in the "include" directory.
%
%Part of the Simulink MAVLink package.
%(c) Aditya Joshi, October 2017


%% Create and save bus

disp('**')

fprintf('Creating Simulink bus from message... ');
[simulink_bus, simulink_bus_name] = create_bus_from_mavlink_header(filename);
assignin('base',simulink_bus_name,simulink_bus);
disp('done');
eval([simulink_bus_name '= simulink_bus;'])
busfilename = ['buses/bus_' simulink_bus_name '.mat'];
save(busfilename,simulink_bus_name);
disp(['Bus is saved in ' busfilename]);


%% Prepare header file

fprintf('Creating the s-function header file... ');
mavlink_msg_name = erase(simulink_bus_name,{'mavlink_','_t'});
fileName = ['include/sfun_mavlink_msg_' mavlink_msg_name '.h'];
fid = fopen(fileName,'w');


%% Write header

fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','DO NOT EDIT.');
fprintf(fid,'%s\n',['This file was automatically created by the Matlab function ''create_sfun_header'' on ' datestr(now)]);
fprintf(fid,'%s\n','as part of Simulink MAVLink library.');
fprintf(fid,'%s\n','*/');

% Use full path in the #include statements
pathname = fileparts(mfilename('fullpath'));
sep = filesep;
fprintf(fid,'%s\n','');
fprintf(fid,'%s\n',['#include "' pathname sep 'include' sep 'mavlink' sep 'v1.0' sep 'common' sep 'mavlink_msg_' mavlink_msg_name '.h"']);
fprintf(fid,'%s\n',['#define BUS_NAME_' upper(mavlink_msg_name) ' "' simulink_bus_name '"']);
fprintf(fid,'%s\n',['#define NFIELDS_BUS_' upper(mavlink_msg_name) ' ' num2str(length(simulink_bus.Elements))]);
fprintf(fid,'%s\n',['#define ENCODED_LEN_' upper(mavlink_msg_name) ' (MAVLINK_NUM_NON_PAYLOAD_BYTES + MAVLINK_MSG_ID_' upper(mavlink_msg_name) '_LEN)']);


%% encode_businfo function

fprintf(fid,'%s\n','');
fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','Encode the busInfo vector. This vector stores the starting index and total offset');
fprintf(fid,'%s\n','for every element of the message bus. This is the standard way Simulink s-functions');
fprintf(fid,'%s\n','handle bus interfaces.');
fprintf(fid,'%s\n','*/');
fprintf(fid,'%s\n',['static inline void encode_businfo_' mavlink_msg_name '(SimStruct *S, int_T *busInfo, const int_T offset)']);
fprintf(fid,'%s\n','{');
fprintf(fid,'\t%s\n','slDataTypeAccess *dta = ssGetDataTypeAccess(S);');
fprintf(fid,'\t%s\n','const char *bpath = ssGetPath(S);');
fprintf(fid,'\t%s\n',['DTypeId BUSId = ssGetDataTypeId(S, BUS_NAME_' upper(mavlink_msg_name) ');']);
fprintf(fid,'\t%s\n','');

for i = 1:length(simulink_bus.Elements)
    fprintf(fid,'\t%s\n',['busInfo[offset+' num2str(2*(i-1)) '] = dtaGetDataTypeElementOffset(dta, bpath, BUSId, ' num2str(i-1) ');']);
    fprintf(fid,'\t%s',['busInfo[offset+' num2str(2*(i-1)+1) '] = ']);
    if simulink_bus.Elements(i).Dimensions > 1
        fprintf(fid,'%s',[num2str(simulink_bus.Elements(i).Dimensions) '* ']);
    end
    fprintf(fid,'%s\n',['dtaGetDataTypeSize(dta, bpath, ssGetDataTypeId(S, "' simulink_bus.Elements(i).DataType '"));']);
end

fprintf(fid,'\t%s\n','ssSetUserData(S, busInfo);');
fprintf(fid,'%s\n','}');
fprintf(fid,'%s\n','');


%% encode_vector function

fprintf(fid,'%s\n','');
fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','Encode the incoming character vector into the MAVLink bitstream. This process');
fprintf(fid,'%s\n','consists of two stages - encode this character vector into a bus (using the');
fprintf(fid,'%s\n','busInfo vector), and pass this struct to the MAVLink library to encode it into');
fprintf(fid,'%s\n','a bitstream.');
fprintf(fid,'%s\n','*/');
fprintf(fid,'%s\n',['static inline uint16_t encode_vector_' mavlink_msg_name '(const char *uvec, const int_T *busInfo, uint8_T *yvec, const int_T offset)']);
fprintf(fid,'%s\n','{');
fprintf(fid,'\t%s\n',['mavlink_' mavlink_msg_name '_t ubus;']);
fprintf(fid,'\t%s\n','mavlink_message_t msg_encoded;');
fprintf(fid,'\t%s\n','');

for i = 1:length(simulink_bus.Elements)
    fprintf(fid,'\t%s','(void) memcpy(');
    if simulink_bus.Elements(i).Dimensions == 1
        fprintf(fid,'%s','&');
    end
    fprintf(fid,'%s\n',['ubus.' simulink_bus.Elements(i).Name ', uvec + busInfo[offset+' num2str(2*(i-1)) '], busInfo[offset+' num2str(2*(i-1)+1) ']);']);
end

fprintf(fid,'\t%s\n','');
fprintf(fid,'\t%s\n',['mavlink_msg_' mavlink_msg_name '_encode(SYS_ID, COMP_ID, &msg_encoded, &ubus);']);
fprintf(fid,'\t%s\n','return mavlink_msg_to_send_buffer(yvec, &msg_encoded);');
fprintf(fid,'%s\n','}');
fprintf(fid,'%s\n','');


%% decode_msg function

fprintf(fid,'%s\n','');
fprintf(fid,'%s\n','/*');
fprintf(fid,'%s\n','Decode the incoming MAVLink message into an output character vector. This process');
fprintf(fid,'%s\n','consists of two stages - use the MAVLink library to convert the MAVLink message');
fprintf(fid,'%s\n','into its appropriate struct, and then decode this struct into the output character');
fprintf(fid,'%s\n','vector according to busInfo.');
fprintf(fid,'%s\n','*/');
fprintf(fid,'%s\n',['static inline void decode_msg_' mavlink_msg_name '(const mavlink_message_t* msg_encoded, const int_T *busInfo, char *yvec, const int_T offset)']);
fprintf(fid,'%s\n','{');
fprintf(fid,'\t%s\n',['mavlink_' mavlink_msg_name '_t ybus;']);
fprintf(fid,'\t%s\n',['mavlink_msg_' mavlink_msg_name '_decode(msg_encoded, &ybus);']);
fprintf(fid,'\t%s\n','');

for i = 1:length(simulink_bus.Elements)
    fprintf(fid,'\t%s',['(void) memcpy(yvec + busInfo[offset+' num2str(2*(i-1)) '], ']); 
    if simulink_bus.Elements(i).Dimensions == 1
        fprintf(fid,'%s','&');
    end
    fprintf(fid,'%s\n',['ybus.' simulink_bus.Elements(i).Name ', busInfo[offset+' num2str(2*(i-1)+1) ']);']);
end

fprintf(fid,'%s\n','}');


fclose(fid);
disp('done');
disp(['Header file is saved in ' fileName]);

disp('**')
