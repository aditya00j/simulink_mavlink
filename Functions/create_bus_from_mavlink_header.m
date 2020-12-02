function [busObj, bus_name, bus_orig_dtypes] = create_bus_from_mavlink_header(filename)
% CREATE_BUS_FROM_MAVLINK_HEADER: Create a Simulink Bus from a MAVLink message header file
%
% Input: string containing the header file name.
% Output: 
%    busObj: bus object
%    bus_name: string containing name of the bus
%    bus_orig_dtypes: struct containing original datatypes for the bus
%            elements (as found in the MAVLink header)
% 
%Part of the Simulink MAVLink package.
%(c) Aditya Joshi, October 2017

fid = fopen(filename, 'r');
datatypes = readtable('datatype_map.csv','ReadVariableNames',1);

% Assume that the first line containing "typedef struct __" is the message
% definition.
lin = fgetl(fid);
while ~startsWith(lin, 'typedef struct __')
    lin = fgetl(fid);
end

% Extract bus name
bus_name = strtrim(erase(lin,{'typedef struct __','{'}));
bus_orig_dtypes = struct;

% Now you have fields until you hit "}"
nfields = 0;
lin = fgetl(fid);
while ~contains(lin,'}')
    data = regexp(lin,'\;','split');
    description = strtrim(erase(data{2},{'/*<','*/'}));
    data = textscan(data{1},'%s');
    data = data{1};
    datatype = data{1};
    name = data{2};
    dimensions = regexp(name,'\[(\d*)\]','match');
    if isempty(dimensions)
        dimensions = 1;
    else
        % DO NOT CHANGE the following to str2double
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
        bus_orig_dtypes.(name) = char(datatypes.px4(idx));
    end
    lin = fgetl(fid);
end

busObj = Simulink.Bus;
busObj.Elements = busElements;

fclose(fid);
