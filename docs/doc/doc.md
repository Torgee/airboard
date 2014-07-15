
# Airboard Documentation

## Current State: SimpleSimu

At the moment, there is only one working module in this project, namely 'simplesimu'. This module is merely proof of concept and consists of a simple server 'simple_sensor', that simulates streaming sensor data in form of a dobule value and a corresponding timestamp via a zmq-socket (or rather multiple, as tcp and ipc are available currently), using googles protobuf for encoding. And multiple varieties of receivers 'simple_receiver', 'receiver.py' and 'receiver_kivy.py', that receive the stream and either measure throughput,display the values, or both.

### Building

For the c++ programs (simple_sensor and simple_receiver), build the corresponding Makefiles (Makefile.sensor and Makefile.receiver respectively) using make. There is also a 'clear' target in both.
There is also a 'master' makefile, simply called 'Makefile', that will build both programs.
For the python programs, just run the scripts with python.

### DataFlow

A data package consists of a timestamp and a double precision floating point value. Its protobuf definition is in the 'double.prot' file.
The simple_sensor (server/publisher) publishes data packages with a given frequency (see [Running the Server/Streamer]) via zmq on a PUB-socket using the following connections:
 - tcp://*:5556 (localhost)
 - ipc://tmp/sensor.ipc
Receivers may connect to either with a zmq SUB-socket.
No topics are used, so subscription to '' is used to receive all messages.

### Running the Server/Streamer
The server program is called 'simple_sensor' and can be run from the commandline with one integer parameter denoting the publishing interval in milliseconds. Negative values are valid and will make the publishing 'as fast as possible', which is considerably faster than using '0' as a parameter (probably depending on implementation, tested on linux mint 15 with g++ 4.7.3).
The server will periodically send a constant value, which can be changed during runtime and defaults to '2.0'. To change the value, enter the desired number to stdin.
An invalid argument (i.e. not parseable to double),or an empty line, will terminate the program.

example:
$./simple_sensor 200
# publishes a '2.0' every 200ms
>3.4
# changes the static value from '2.0' to '3.4'
>
# empty line to end the program

### Running the Clients/Receiver

#### 'simple_receiver'

This c++-base program can be run from the commandline and will receive a number of messages via ipc. The number of messages to be received is defined by the first command line argument and defaults to 10000 for negative values. When the given number of messages is received, the program displays the total and mean time it took to receive the messages and terminates.

Note: the program will receive one extra messages before starting the time measurement as a warmup.

#### 'receiver.py'

This python based program receives messages via ipc until it's stopped via issuing a KeyboardInterrupt, aka Ctrl+C.
Pass '-v' on the commandline to print all received messages to stdout.

#### 'receiver_kivy.py'

This program uses kivy to display the last 5 messages received on a simple GUI consisting of just one simple label.

#### 'receiver_pygame.py'

This program was never running properly and is deprecated!!!
