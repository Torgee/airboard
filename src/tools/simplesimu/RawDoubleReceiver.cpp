

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
	//m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"",strlen(""));
	m_sub_socket.setsockopt(ZMQ_SUBSCRIBE,"2",strlen("2"));
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
	
	//zmq::message_t message(6+1);
	//m_sub_socket.recv(message.data(),6+1);
	
	std::cout << "received something! - len:"
			<< message.size() << std::endl;
	std::cout << "message: '"
			<< std::string(static_cast<char*>(message.data()))
			<< "'" << std::endl;
	//
	//m_sub_socket.recv(&m_message);
	//m_sub_socket.recv(m_message.data(),sizeof(double));
	//
	//std::cout << "received something! - len:"
			//<< m_message.size() << std::endl;
	
	// only accept messages the size of doubles or crash!
	//assert(m_message.size() == sizeof(double)
			//&& "invalid message size!");



	//std::cout << "message: '"
			//<< std::string(static_cast<char*>(m_message.data()))
			//<< "'" << std::endl;
			
	
	//return *reinterpret_cast<double*>(m_message.data());
	return *static_cast<double*>(m_message.data());
}
