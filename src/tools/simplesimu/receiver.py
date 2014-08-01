

import sys
import timeit
import tempfile

import zmq

import double_pb2

verbose = True if '-v' in sys.argv else False

#  Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Collecting updates from sensor")
tempdir = tempfile.gettempdir()
ipcport = "ipc://{}/sensor.ipc".format(tempdir)
socket.connect(ipcport)
print("Listening to {}-port: {}".format('ipc',ipcport))

# Subscribe to all messages
socket.setsockopt_string(zmq.SUBSCRIBE, u"")

i=0

# warm up
msg = socket.recv()


last = 0
start = timeit.default_timer()
while(True):
	try:
		msg = socket.recv()
		raw_d = double_pb2.RawDouble.FromString(msg)
	except KeyboardInterrupt:
		break
	else:
		if verbose:
			print raw_d
		i+=1
		last = timeit.default_timer()
		#print raw_d.value
	
time_spent = last-start
if i == 0:
	print 'no message received!'
else:
	print 'received {} messages in {}s\n{}s/msg\n{}hz'.format(
			i,time_spent,time_spent/i,i/time_spent)

