
#include <iostream>

#include "RawDoubleReceiver.h"

#include "zmq.hpp"

int main(int argc, char** argv){
	
	// initialize zeromq context
	zmq::context_t context(1);
	
	// will notify for recieved events via std::out for now ...
	RawDoubleReceiver receiver(context);
	
	
	while(true){
		std::cout << "try receive: ..." << std::endl;
		std::cout << "value: " << receiver.recieve() << std::endl;
	}

	return 0;
}
