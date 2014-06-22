

import sys

import double_pb2

import zmq

import kivy
kivy.require('1.0.6') # replace with your current kivy version !

from kivy.app import App
from kivy.clock import Clock
from kivy.uix.button import Button
from kivy.uix.label import Label




class MyApp(App):
	def __init__(self,receiver):
		super(MyApp,self).__init__()
		self.receiver = receiver
		
	def build(self,**kwargs):
		return ReceiverLabel(self.receiver,text='n.a.')

class Receiver():
	def __init__(self,parser):
		"""
		'parser' is called with the recieved message in 'self.recv()'
		"""
		self.parser = parser
		
		#  Socket to talk to server
		self.context = zmq.Context()
		self.socket = self.context.socket(zmq.SUB)
		
		# set High-Water-Mark to 1, so basically disabling the message
		# queue, 'cause it'ss likely that the GUI will not keep up with
		# the stream
		# Note: possible solution is to put the receiver in a dedicated
		#       thread/process, which is planned for the future!
		#self.socket.setsockopt(zmq.RCVHWM, 1)
		self.socket.set_hwm(1)
		print self.socket.hwm
		
		self.socket.connect("ipc:///tmp/sensor.ipc")
		
		# Subscribe to all messages
		self.socket.setsockopt_string(zmq.SUBSCRIBE, u"")

		
	def recv(self):
		return self.parser(self.socket.recv())

class ReceiverLabel(Label):
	def __init__(self,receiver,**kwargs):
		super(ReceiverLabel,self).__init__(**kwargs)
		self.receiver = receiver
		Clock.schedule_interval(self.recv,0)
		
	def recv(self,dt=0):
		self.text = str(self.receiver.recv())

if __name__ == '__main__':
	#assert False,'not ready!'
	
	# use the string-parsing function generated from protoc
	recv = Receiver(double_pb2.RawDouble.FromString)
	
	print("Collecting updates from sensor")
	parsed_msg = recv.recv()
	print parsed_msg
	MyApp(recv).run()
	
