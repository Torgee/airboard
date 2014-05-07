

#include "RawDoubleReceiver.h"

#include <iostream>
#include <string>

RawDoubleReceiver::RawDoubleReceiver(zmq::context_t &context)
		: m_sub_socket(context,ZMQ_SUB),
		
		// give message-'buffer' the desired fixed size
		m_message(sizeof(double)+1)
{
	
	m_sub_socket.connect("tcp://localhost:5556");
	//m_sub_socket.connect("ipc://sensor.ipc");
	m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"",strlen(""));
	//m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"2",strlen("2"));
	//m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"",1);
	
	std::cout << "strlen(\"\"): " << strlen("") << std::endl;
}


RawDoubleReceiver::~RawDoubleReceiver()
{
	;
}


double RawDoubleReceiver::recieve()
{
	zmq::message_t message;
	m_sub_socket.recv(&message);
	
	std::cout << "received something! - len:"
			<< message.size() << std::endl;
	std::cout << "message: '"
			<< std::string(static_cast<char*>(message.data()))
			<< "'" << std::endl;
	std::cout << "as double: "
			<< *(static_cast<double*>(message.data()))
			<< std::endl;

	return *static_cast<double*>(message.data());
}
