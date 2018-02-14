function [busObj, bus_name, bus_orig_dtypes] = create_bus_from_mavlink_header(filename)
% CREATE_BUS_FROM_MAVLINK_HEADER: Create a Simulink Bus from a single 
% MAVLink message header file
% 
% NOTE: This function is called by another function create_sfun_header,
%       so the user would typically not have to directly use this function.
%
% Input: string containing the MAVLink message header file name
% 
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

% Skip lines till "MAVPACKED"
lin = fgetl(fid);
while ~contains(lin,'MAVPACKED')
    lin = fgetl(fid);
end

% Next line is "typedef struct" - extract bus name from this
lin = fgetl(fid);
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
        dimensions = str2num(dimensions{1});
        name = regexp(name,'\[(\d*)\]','split');
        name = name{1};
    end

    idx = find(strcmp(datatype,datatypes.mavlink), 1);
    if isempty(idx)
        error(['Could not find datatype ' datatype ' in datatype_map.csv'])
    else
        nfields = nfields + 1;
        busElements(nfields) = Simulink.BusElement;
        busElements(nfields).Name = name;
        busElements(nfields).DataType = char(datatypes.simulink(idx));
        busElements(nfields).Dimensions = dimensions;
        busElements(nfields).Description = description;
        bus_orig_dtypes.(name) = char(datatypes.mavlink(idx));
    end
    lin = fgetl(fid);
end

busObj = Simulink.Bus;
busObj.Elements = busElements;

fclose(fid);
