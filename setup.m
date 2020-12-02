% Example set up file for creating the Simulink models for exchanging
% MAVLink messages with PX4 according to the Simulator MAVLink API:
% https://dev.px4.io/master/en/simulation/index.html

% In this example, a single message, attitude, is sent from one port from
% Simulink and received and decoded on another port. This process tests
% that the MAVLink encoding/decoding works correctly. You can then change
% the options below to include whichever messages need to be
% encoded/decoded for your application.


%% Set up paths and configuration options

addpath(genpath(cd));

% Full path to the directory where MAVLink messages are located
% (DO NOT use relative path)
mavlink_path = '/Users/aditya/Documents/PX4/mavlink/include/mavlink/v2.0/common';


% Select messages to send
messages_to_send = {
    'attitude';
    };

% Select messages to receive
messages_to_receive = {
    'attitude';
    };


%% Write and compile S-Functions

% Individual encoders for each message to send
for i = 1:length(messages_to_send)
    filename = strcat(mavlink_path, '/mavlink_msg_', messages_to_send{i}, '.h');
    create_sfun_encode(filename);
end

% Single decoder for all received messages
filenames = cell(size(messages_to_receive));
for i = 1:length(messages_to_receive)
    filenames{i} = strcat(mavlink_path, '/mavlink_msg_', messages_to_receive{i}, '.h');
end
create_sfun_decode(filenames);
