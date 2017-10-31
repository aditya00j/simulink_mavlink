% Example for creating and saving a Simulink bus for a MAVLink message

% Get the output structure
busOut = create_bus_from_mavlink_header('mavlink_msg_attitude.h');

% Save the bus object. The above structure also extracts the name of the
% message struct used in MAVLink. It is a good idea to use the same name
% for the bus.
assignin('base',busOut.name,busOut.bus);

% Save this bus object. You will need to import it into your base workspace
% any time you are using the s-function.
filename = ['buses/bus_' busOut.name '.mat'];
save(filename, busOut.name);
