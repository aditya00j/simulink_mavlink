function busData = create_bus_from_mavlink_header(filename)
% CREATE_BUS_FROM_MAVLINK_HEADER: Create a Simulink Bus from a MAVLink message header file
%
% Input: string containing the header file name.
% Output: a struct containing following fields -
%           name: bus name, extracted from the message struct name
%           bus: actual bus object
% Example: create_bus_from_mavlink_header('mavlink_msg_altitude.h') will create
%          a bus object for the altitude message.
%
%Part of the Simulink MAVLink package.
%(c) Aditya Joshi, October 2017

busData = struct;
fid = fopen(filename, 'r');
datatypes = readtable('datatype_map.csv','ReadVariableNames',1);

% Skip lines till "MAVPACKED"
lin = fgetl(fid);
while ~contains(lin,'MAVPACKED')
    lin = fgetl(fid);
end

% Next line is "typedef struct" - extract bus name from this
lin = fgetl(fid);
lin = strrep(lin,'typedef struct __','');
lin = strrep(lin,'{','');
busData.name = strtrim(lin);

% Now you have fields until you hit "}"
nfields = 0;
lin = fgetl(fid);
while ~contains(lin,'}')
    data = regexp(lin,'\;','split');
    description = erase(data{2},{'/*< ','*/'});
    data = textscan(data{1},'%s');
    data = data{1};
    datatype = data{1};
    name = data{2};
    dimensions = regexp(name,'\[(\d*)\]','match');
    if isempty(dimensions)
        dimensions = 1;
    else
        dimensions = str2num(dimensions{1});
        name = regexp(name,'\[(\d*)\]','split');
        name = name{1};
    end
        
    idx = find(strcmp(datatype,datatypes.px4), 1);
    if isempty(idx)
        error(['Could not find datatype ' datatype ' in datatype_map.csv'])
    else
        nfields = nfields + 1;
        busElements(nfields) = Simulink.BusElement;
        busElements(nfields).Name = name;
        busElements(nfields).DataType = char(datatypes.simulink(idx));
        busElements(nfields).Dimensions = dimensions;
        busElements(nfields).Description = description;
    end
    lin = fgetl(fid);
end

busData.bus = Simulink.Bus;
busData.bus.Elements = busElements;

fclose(fid);
