

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

class ZMQReceiver():
	def __init__(self,parser):
		"""
		'parser' is called with the recieved message in 'self.recv()'
		"""
		self.parser = parser
		
		#  Socket to talk to server
		self.context = zmq.Context()
		self.socket = self.context.socket(zmq.SUB)
		
		# seems not to work :/
		## set High-Water-Mark to 1, so basically disabling the message
		## queue, 'cause it's likely that the GUI will not keep up with
		## the stream
		## Note: possible solution is to put the receiver in a dedicated
		##       thread/process, which is planned for the future!
		##self.socket.setsockopt(zmq.RCVHWM, 1)
		#self.socket.set_hwm(1)
		#print self.socket.hwm
		
		self.socket.connect("ipc:///tmp/sensor.ipc")
		
		# Subscribe to all messages
		self.socket.setsockopt_string(zmq.SUBSCRIBE, u"")

		
	def recv(self):
		return self.parser(self.socket.recv())
		
	def try_recv_latest(self):
		try:
			msg = self.socket.recv(flags = zmq.NOBLOCK)
		except zmq.ZMQError as e:
			raise BufferError(e)
		
		while(True):
			try:
				temp = self.socket.recv(flags = zmq.NOBLOCK)
			except zmq.ZMQError:
				break
			else:
				msg = temp
		
		return self.parser(msg)



class ReceiverLabel(Label):
	def __init__(self,receiver,**kwargs):
		super(ReceiverLabel,self).__init__(**kwargs)
		self.receiver = receiver
		#Clock.schedule_interval(self.recv,0)
		# update only every 0.05s at max, to limit cpu use
		Clock.schedule_interval(self.try_recv_latest,0.1)
		
	def recv(self,dt=0):
		self.text = str(self.receiver.recv())
		
	def try_recv_latest(self,dt=0):
		"""
		discards all previous messages that are in a buffer potentially
		does nothing if buffer is empty (no message to be received)
		"""
		try:
			self.text = str(self.receiver.try_recv_latest())
		except BufferError:
			pass
			

if __name__ == '__main__':
	
	# use the string-parsing function generated from protoc
	recv = ZMQReceiver(double_pb2.RawDouble.FromString)
	
	print("Collecting updates from sensor")
	MyApp(recv).run()
	
