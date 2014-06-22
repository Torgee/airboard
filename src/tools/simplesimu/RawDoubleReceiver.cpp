

#include "RawDoubleReceiver.h"

#include "double.prot.pb.h"

#include <iostream>
#include <string>

RawDoubleReceiver::RawDoubleReceiver(zmq::context_t &context)
		: m_sub_socket(context,ZMQ_SUB)
{
	
	//m_sub_socket.connect("tcp://localhost:5556");
	m_sub_socket.connect("ipc:///tmp/sensor.ipc");
	m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"",strlen(""));
	//m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"2",strlen("2"));
	//m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"",1);
	
	//std::cout << "strlen(\"\"): " << strlen("") << std::endl;
}


RawDoubleReceiver::~RawDoubleReceiver()
{
	;
}


double RawDoubleReceiver::receive()
{
	zmq::message_t message;
	m_sub_socket.recv(&message);
	RawDouble rawDouble;
	
	std::string buffer(static_cast<char*>(message.data()));
	std::cout << "received something! - len:"
			<< message.size() << std::endl;
	std::cout << "message: '"
			<< buffer
			<< "'" << std::endl;
	//std::cout << "as double: "
			//<< *(static_cast<double*>(message.data()))
			//<< std::endl;
	rawDouble.ParseFromArray(message.data(),message.size());
	std::cout << "from RawDouble: "
			<< rawDouble.value()
			<< std::endl;
	

	return rawDouble.value();
	//return *static_cast<double*>(message.data());
}
