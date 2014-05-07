
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>


#include "RawDoubleSensorModule.h"

#include "zmq.hpp"


int main(int argc, char** argv)
{
	// initialize zeromq context
	zmq::context_t context(1);
	
	// *** parameter setup ***
	// first use a constant value, random will be added later
	// (together with command line arguments!)
	
	//// random values in between [low,high), i.e.:
	//// val = low + [0.0,1.0) * (high-low)
	//double low = 0.0;
	//double high = 1.0;
	//double samplingRate = 200.; // in Hz
	double value = 2.0; // in no particular unit
		
	// publishing will be to stdout first, but soon to be changed
	// to use a publisher/notifier!
	//Publisher pub;
	//SensorModule sensmod(pub);
	std::chrono::milliseconds interval(1000);
	//std::chrono::milliseconds interval(500);
			//= RawDoubleSensorModule::DEFAULT_INTERVAL;
			//= 500;
	
	
	RawDoubleSensorModule sensorModule(value,interval,context);
	//sensorModule.start();
	
	
	// removed
	//// show that main thread is still alive
    //std::chrono::seconds duration(1);
	//while(true){
	//for(int i=0;i<20;++i){
		//std::cout << "--- main thread alive!" << std::endl;
		//std::this_thread::sleep_for( duration );
	//}
	
	// ToDo: try to cope for ctrl-c, as the ipc-pipe will not be
	// destroyed otherwise
	// Note: the following does NOT work!
	try{
		std::cin.get();
		//std::this_thread::sleep_for(std::chrono::seconds(60));
		//std::chrono::seconds duration(1);
		//while(true){
		//for(int i=0;i<20;++i){
			//std::cout << "--- main thread alive!" << std::endl;
			//std::this_thread::sleep_for( duration );
		//}
	} catch(...){ //seems not to work for ctrl-c ...
		std::cout << "exception catched!" << std::endl;
	}
	
	return 0;
}

