
# Airboard Documentation

## Current State: SimpleSimu

At the moment, there is only one working module in this project, namely 'simplesimu'. This module consists of a simple server 'simple_sensor', that simulates streaming sensor data in form of a dobule value and a corresponding timestamp via a zmq-socket (or rather multiple, as tcp and ipc are available currently), using googles protobuf for encoding. And multiple varieties of receivers 'simple_receiver', 'receiver.py' and 'receiver_kivy.py', that receive the stream and either measure throughput,display the values, or both.

### DataFlow

### Running the Server/Streamer

### Running the Clients/Receiver
