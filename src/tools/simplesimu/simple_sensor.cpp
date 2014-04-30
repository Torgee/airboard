
#include <chrono>
#include <iostream>
#include <string>
#include <thread>


#include "RawDoubleSensorModule.h"


int main(int argc, char** argv)
{
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
	std::chrono::milliseconds interval(500);
			//= RawDoubleSensorModule::DEFAULT_INTERVAL;
			//= 500;
	
	
	RawDoubleSensorModule sensorModule(value,interval);
	//sensorModule.start();
	
	
	// removed
	//// show that main thread is still alive
    //std::chrono::seconds duration(1);
	//while(true){
	//for(int i=0;i<20;++i){
		//std::cout << "--- main thread alive!" << std::endl;
		//std::this_thread::sleep_for( duration );
	//}
	
	return 0;
}

