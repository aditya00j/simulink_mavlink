# Simulink-MAVLink v2.0
**MAVLink communication support for Simulink**

![Encode Image](https://raw.githubusercontent.com/aditya00j/simulink_mavlink/master/images/example_encode.PNG)
![Decode Image](https://raw.githubusercontent.com/aditya00j/simulink_mavlink/master/images/example_decode.PNG)
___

## What is Simulink-MAVLink?
 * [MAVLink] library essentially serializes structured messages into uint8 vectors (bit streams).
 * Encoding a MAVLink message means taking structured data and packing it into a bit stream.
 * Decoding an incoming MAVLink bit stream means storing the uint8 data into a memory buffer, and extracting the desired messages into their structures.
 * Simulink already has capabilities to send and receive bit streams on communication channels such as UDP and serial.
 * Simulink also has a way of representing structured numerical data - Simulink Bus.
 * Therefore, this small and light-weight Simulink-MAVLink library was built to provide Simulink S-functions utilizing the MAVLink library, which facilitate two-way data conversion: Simulink Bus to uint8, and uint8 to Simulink Bus.

This library was built and tested on Matlab R2017a.

[MAVLink]: https://github.com/mavlink/mavlink

 ## How to get started?
  1. Get MAVLink header files for any dialect (e.g. "common", provided by default with this library).
  2. Identify the messages that you wish to send or receive.
  3. For each message, run the Matlab function "create_sfun_encode" provided in this library. It will create and save a Simulink bus for this message, create the header and source files for the s-function, and finally compile the s-function. **Note that you have to load the bus into your workspace when you use this s-function in Simulink.**
  4. For decoding particular messages from an incoming MAVLink stream, run the Matlab function "create_sfun_decode". This will create and save Simulink buses for all the messages you selected, create the headers and source file for the s-function, and finally compile the s-function.
  5. Use the compiles s-functions in Simulink.

  See the "examples" folder for an example of this process.


  ## Following general principles were used in formulating this library:
   1. Do not recreate any functionality that already exists either in Simulink or MAVLink - only build the absolute minimum bridges required in the interface. This ensures wide applicability and inter-operability.
   2. Make the interfaces as explicit as possible. This puts the onus of ensuring correct datatypes and other run-time issues on the user, instead of having to cater for non-standard conditions in this library.
   3. Provide only the two-way data conversion capability, and nothing else.


  ## Notes
   * **Terms of Use:** I created this library for my personal use. I've tried to make it abstract in its formation, but it may or may not suit your needs. There are other excellent implementations for Matlab-MAVLink interface online which you can use. They didn't suit my needs exactly, so I wrote this small library. I am releasing it here for common good, without assuming any responsibility of its accuracy or future support. And like all open source software, you are agreeing to these terms by using this library. It's extremely unlikely that your computer will burst into flames by using this library, but nothing's impossible!
   * **Combining messages:** Logically, you need to write one s-function for encoding each message. The bit streams for all these messages can be combined using standard Simulink blocks like "Byte Pack" or a simple Mux, before sending them over a communication channel. This follows from Principle 1 above. On the other hand, during decoding, you have only one bit stream per MAVLink channel. It means you can have only 1 s-function for decoding all messages. This process is shown in the example included.
   * **Why Buses?:** For most MAVLink messages, you can simply use a vector of the type "double", which is the standard Simulink signal. However, following Principle 2 above, the s-function should not make any (incorrect) assumptions about the data types. Therefore, the best way to ensure that the user correctly packs and unpacks a MAVLink message is to provide a transparent interface. A Simulink Bus is the best way to do that. It might seem like a chore to uses buses for simple messages, but in general it's better. Plus, since the bus objects are automatically created from the MAVLink headers, they are explicitly guaranteed to be compatible. Another advantage is that the meta-data related to the message elements is also extracted into the bus, which can be used for a quick reference in Simulink.
   * **Unsupported data types:** Simulink does not support "uint64" data type. This is used in many messages for logging time. The type "double" is used as a surrogate for it in the bus object. This hasn't given me any errors until now, since typecasting between "uint64" and "double" works in most cases. But you should be aware of this difference. Also, some MAVLink messages have character arrays storing non-numerical data. Obviously, this cannot be used directly in Simulink, so they are typecast into "uint8". In Simulink, you can convert the characters into uint8 before passing them to the s-function (e.g. "uint8('HELLO')"). The data type conversion between MAVLink struct and Simulink Bus is defined in the file "datatype_map.csv".
