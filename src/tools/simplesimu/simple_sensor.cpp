
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
	
	std::chrono::milliseconds interval(argc > 1 ?
			atoi(argv[1]) : 100);
	//std::chrono::milliseconds interval(500);
			//= RawDoubleSensorModule::DEFAULT_INTERVAL;
			//= 500;
	
	
	RawDoubleSensorModule sensorModule(value,interval,context);
	//sensorModule.start();
	
	
	bool goOn = true;
	std::string line;
	decltype(value) newValue;

	// Note: This is no busy wait! Rather a very basic and limited interpreter,
	//       while processing (i.e. sending data) is running in a seperate thread
	while(goOn){
		std::getline(std::cin,line);
		
		try {
			newValue = std::stod(line);
			sensorModule.setValue(newValue);
		} catch (...) {
			goOn = false;
		}
	}

	
	return 0;
}

