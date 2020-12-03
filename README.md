# Simulink-MAVLink
**MAVLink communication support for Simulink**

![Encode Image](Images/example_encode.PNG)
![Decode Image](Images/example_decode.PNG)
___

## What is Simulink-MAVLink?

 * [MAVLink] library essentially serializes structured messages into uint8 vectors (bit streams).
 * Encoding a MAVLink message means taking structured data and packing it into a bit stream.
 * Decoding an incoming MAVLink bit stream means storing the uint8 data into a memory buffer, and extracting the desired messages into their structures.
 * Simulink already has capabilities to send and receive bit streams on communication channels such as TCP/UDP and UART.
 * Simulink also has a way of representing structured numerical data - Simulink Bus.
 * Therefore, this small and light-weight Simulink-MAVLink library was built to provide Simulink S-functions utilizing the MAVLink library, which facilitate two-way data conversion: Simulink Bus to uint8, and uint8 to Simulink Bus.

This library was built and tested on Matlab R2017a.

[MAVLink]: https://github.com/mavlink/mavlink

## Getting Started

### Step 1: Create Message Busses and S-Functions
 
1. Use the script `setup.m` to choose which MAVLink messages need to be encoded/decoded for your application.
2. Running the script will create the message busses, write the header and source files for the message encoder and decoder functions, and finally compile the s-functions using the `mex` command. Assuming all the options are specified correctly and the mex compilation is working, the compiled S-functions are created in the `Generated` folder.

For each message to be encoded, a separate S-function is created, that accepts the message bus as input, and creates a uint8 array of length `MAVLINK_MAX_PACKET_LEN` (= 280 for MAVLink v2.0).

On the other hand, for decoding the received MAVLink data, there is only a single S-function, which accepts a uint8 array of length `NMAX * MAVLINK_MAX_PACKET_LEN`, where `NMAX` is a user-specified maximum number of messages to be decoded in one iteration. This can be determined from the amount of buffer used in the receiving channel. The decoder S-function has `n+1` output ports, where `n` is the number of messages selected for decoding. The first output is a vector of length `n`, which indicates a 1/0 received status for each message received. If a message is received and decoded successfully in a given iteration, the status for that message is set to 1, otherwise 0. The output ports 2 onwards are the message busses, into which the decoded data is unpacked.


### Step 2: Use S-Functions in Simulink to Test Local Encoding/Decoding

To verify that the encoding/decoding works correctly, open the Simulink model `Examples\test_messages_local.slx`. This model packs the messages 'ping' and 'param_set' into a single uint8 stream using their encoder functions, and then decodes this stream using the decoder function. Note the following points while running the model:

* All the message busses must be loaded into the base workspace before running the model.
* The signal on the input port of an encoder S-function must be a non-virtual bus, and all the individual signal types for the bus input must be set correctly.


## General Principles
Following general principles were used in formulating this library:

1. Do not recreate any functionality that already exists either in Simulink or MAVLink - only build the absolute minimum bridges required in the interface. This ensures wide applicability and inter-operability.
2. Make the interfaces as explicit as possible. This puts the onus of ensuring correct datatypes and other run-time issues on the user, instead of having to cater for non-standard conditions in this library.
3. Provide only the two-way data conversion capability, and nothing else.


## Notes
* **Combining messages:** Logically, you need to write one S-function for encoding each message. The bit streams for all these messages can be combined using standard Simulink blocks like "Byte Pack" or a simple Mux, before sending them over a communication channel. On the other hand, during decoding, you have only one bit stream per MAVLink channel. It means you can have only 1 S-function for decoding all messages. This process is shown in the example included.

* **Why Busses?:** For most MAVLink messages, you can simply use a vector of the type "double", which is the standard Simulink signal. However, following Principle 2 above, the s-function should not make any (incorrect) assumptions about the data types. Therefore, the best way to ensure that the user correctly packs and unpacks a MAVLink message is to provide a transparent interface. A Simulink Bus is the best way to do that. It might seem like a chore to uses buses for simple messages, but in general it's better. Plus, since the bus objects are automatically created from the MAVLink headers, they are explicitly guaranteed to be compatible. Another advantage is that the meta-data related to the message elements is also extracted into the bus, which can be used for a quick reference in Simulink.

* **Unsupported data types:** Simulink does not support "uint64" data type. This is used in many MAVLink messages for logging time. The fields of this type are typecast as "double" in the bus object. This hasn't given me any errors until now, since typecasting between "uint64" and "double" works in most cases. But you should be aware of this difference, as theoretically there are some uint64 integers that cannot be stored in double. Also, some MAVLink messages have character arrays storing non-numerical data. Obviously, this cannot be used directly in Simulink, so they are typecast into "uint8". In Simulink, you can convert the characters into uint8 before passing them to the s-function (e.g. "uint8('HELLO')"). The data type conversion between MAVLink struct and Simulink Bus is defined in the file "datatype_map.csv".
