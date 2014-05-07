
#include <iostream>
#include <chrono>

#include "RawDoubleReceiver.h"

#include "zmq.hpp"

using msecs = std::chrono::milliseconds;

int main(int argc, char** argv){
	
	// initialize zeromq context
	zmq::context_t context(1);
	
	// will notify for recieved events via std::out for now ...
	RawDoubleReceiver receiver(context);
	
	int i;
	int nbrOfIters = argc > 1 ? atoi(argv[1]) : 10000;
	// allocate those variables before measuring anything
	decltype(std::chrono::system_clock::now()) start_time,end_time;
	
	start_time = std::chrono::system_clock::now();
	for(i=0;i<nbrOfIters;++i){
	//while(true){
		receiver.receive();
		//std::cout << "try receive: ..." << std::endl;
		//std::cout << "value: " << receiver.recieve() << std::endl;
	}
	end_time = std::chrono::system_clock::now();
	
	int duration = std::chrono::duration_cast<msecs>(end_time - 
			start_time).count();
	std::cout << "received " << i << " messages in "
			<< duration << "msecs" << std::endl;
	std::cout << "average: " << duration/(float)i << std::endl;

	return 0;
}
