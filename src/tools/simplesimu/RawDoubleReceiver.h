 
#ifndef RAWDOUBLERECIEVER_H
#define RAWDOUBLERECIEVER_H

#include "zmq.hpp"

class RawDoubleReceiver {

public:
	RawDoubleReceiver(zmq::context_t &context);
	virtual ~RawDoubleReceiver();
	
	double receive();
	
private:
	zmq::socket_t m_sub_socket;
};

#endif // #ifndef RAWDOUBLERECIEVER_H
