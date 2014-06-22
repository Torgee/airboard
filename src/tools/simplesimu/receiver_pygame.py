

import sys

import zmq
import pygame

import double_pb2


assert False,'not implemented!'

def display_value(value):
	pass

#  Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting updates from sensor")
socket.connect("ipc:///tmp/sensor.ipc")

# Subscribe to all messages
socket.setsockopt_string(zmq.SUBSCRIBE, u"")

msg = socket.recv()
raw_d = double_pb2.RawDouble.FromString(msg)
