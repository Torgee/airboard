 
#ifndef RAWDOUBLERECIEVER_H
#define RAWDOUBLERECIEVER_H

#include "zmq.hpp"

class RawDoubleReceiver {

public:
	RawDoubleReceiver(zmq::context_t &context);
	virtual ~RawDoubleReceiver();
	
	double recieve();
	
private:
	zmq::socket_t m_sub_socket;

	// will be given the static size required for an double in c'tor
	zmq::message_t m_message;
};

#endif // #ifndef RAWDOUBLERECIEVER_H
