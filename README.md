# Simulink-MAVLink v1.0
**MAVLink communication support for Simulink**

![Encode Image](https://raw.githubusercontent.com/aditya00j/simulink_mavlink/master/images/example_encode.PNG)
![Decode Image](https://raw.githubusercontent.com/aditya00j/simulink_mavlink/master/images/example_decode.PNG)
___

## What is Simulink-MAVLink?
 * MAVLink library essentially serializes structured messages into uint8 vectors (bit streams).
 * Encoding a MAVLink message means taking structured data and packing it into a bit stream.
 * Decoding an incoming MAVLink bit stream means storing the uint8 data into a memory buffer, and extracting the desired messages into their structures.
 * Simulink already has capabilities to send and receive bit streams on communication channels such as UDP and serial.
 * Simulink also has a way of representing structured numerical data - Simulink Bus.
 * Therefore, this small and light-weight Simulink-MAVLink library was built to provide Simulink S-functions utilizing the MAVLink library, which facilitate two-way data conversion: Simulink Bus to unit8, and unit8 to Simulink Bus.

This library was built and tested on Matlab R2017a.

 ## How to get started?
  1. Get MAVLink header files for any dialect (e.g. "common", provided by default with this library).
  2. Identify the messages that you wish to send or receive.
  3. For each message, run the Matlab function "create_bus_from_mavlink_header" provided in this library. It will create an output struct, with the bus object and its name. You should save this bus, it will need to be imported into your base workspace any time you use the s-functions for these messages. This process is shown in the example file "example_create_buses.m" in the "examples" folder.
  4. An example s-function header file for the message "attitude" is given in the "include" folder. Create a similar header file for your message. **In future, this header file will be automatically created with a Matlab function.**
  5. Example s-function source files for encoding and decoding this message are given in the "sfunctions" folder. Create the s-functions for your messages from this template. **In future, there will be Matlab functions for automatically creating these s-functions.**
  6. Compile the s-functions using "mex" command in Matlab. The mex functions created for the message "attitude" on Windows (64 bit) are included in the "sfunctions" folder.
  7. Use these compiled s-functions with an "S Function" block in Simulink.

  An example Simulink file for the "attitude" message is provided in the "examples" folder.


  ## Following general principles were used in formulating this library:
   1. Do not recreate any functionality that already exists either in Simulink or MAVLink - only build the absolute minimum bridges required in the interface. This ensures wide applicability and inter-operability.
   2. Make the interfaces as explicit as possible. This puts the onus of ensuring correct datatypes and other run-time issues on the user, instead of having to cater for non-standard conditions in this library.
   3. Provide only the two-way data conversion capability, and nothing else.


  ## Notes
   * **Terms of Use:** I created this library for my personal use. I've tried to make it abstract in its formation, but it may or may not suit your needs. There are other excellent implementations for Matlab-MAVLink interface online which you can use. They didn't suit my needs exactly, so I wrote this small library. I am releasing it here for common good, without assuming any responsibility of its accuracy or future support. And like all open source software, you are agreeing to these terms by using this library. It's extremely unlikely that your computer will burst into flames by using this library, but nothing's impossible!
   * **Combining messages:** Logically, you would write one s-function for encoding each message. The bit streams for all these messages can be combined using standard Simulink blocks like "Byte Pack" or a simple Mux, before sending them over a communication channel. This follows from Principle 1 above. On the other hand, during decoding, you have only one bit stream per MAVLink channel. It means you can have only 1 s-function for decoding all messages. The standard way to handle that would be to create one output port for each message you would like to decode. Currently you would have to extend the given s-function to include this functionality, but I intend to release a Matlab function for automatically creating this s-function.
   * **Why Buses?:** For most MAVLink messages, you can simply use a vector of the type "double", which is the standard Simulink signal. However, following Principle 2 above, the s-function should not make any (incorrect) assumptions about the data types. Therefore, the best way to ensure that the user correctly packs and unpacks a MAVLink message is to provide a transparent interface. A Simulink Bus is the best way to do that. It might seem like a chore to uses buses for simple messages, but in general it's better. Plus, since the bus objects are automatically created from the MAVLink headers, they are explicitly guaranteed to be compatible.
   * **Unsupported data types:** Simulink does not support "uint64" data type. This is used in many messages for logging time. The type "double" is used as a surrogate for it in the bus object. This hasn't given me any errors until now, since typecasting between "uint64" and "double" works in most cases. But you should be aware of this difference. Also, some MAVLink messages have character arrays storing non-numerical data. Obviously, this cannot be used directly in Simulink, so they are typecast into "uint8". In Simulink, you can convert the characters into uint8 before passing them to the s-function (e.g. "uint8('HELLO')"). The data type conversion between MAVLink struct and Simulink Bus is defined in the file "datatype_map.csv".
