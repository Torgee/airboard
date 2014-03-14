
#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <memory>

//#include "simulation/IMUSimulator.h"
//#include "data_streaming/IPC_DataStreamer.h"

#include "sensor/AbstractActiveSensor.h"
#include "sensor/SensorModule.h"
#include "sensor/SensorPoller.h"

#include "sensor/simulation/PassiveSensorSimulator.h"

#include "communication/AbstractPublisher.h"
#include "communication/IPCPublisher.h"



int main(int argc, char** argv)
{
	// *** parameter setup ***
	// ToDo: replace by proper argument parsing OR by calling
	// from python (and to argparse there)
	
	// * simulation parameter
	
	// not supported currently
	//int simulation_type = SIM_RANDOM;
	
	// random values in between [low,high), i.e.:
	// val = low + [0.0,1.0) * (high-low)
	double low = 0.0;
	double high = 1.0;
	double samplingRate = 200.; // in Hz
		
	
	// create all those sensor things
	
	//sptr<RandomDataGenerator> randGen(rg_arams);
	sptr<PassiveRandomSensorSimulator> sensorSimulator_random(low,high);
	//sptr<IPCPublisher> publisher_IPC(ipc_arams);
	sptr<IPCPublisher> publisher_IPC();
	sptr<SensorPoller> sensorSimulatorPoller(
			sensorSimulator_random,sp_params);
	// ToDo: put back here, but currently not working concurrently
	//sensorSimulatorPoller.start();
		
	// create alias for 'dependency injection' kinda
	sptr<AbstractActiveSensor> sensor = simulatorPoller;
	sptr<AbstractPublisher> publisher = publisher_IPC;
	
	SensorModule sensorModule(sensor,publisher)
	
	
	// currently, 'start()' will trigger the polling once
    std::chrono::milliseconds duration(int(1000./samplingRate));
	while(true){
		for(int i=0;i<numberOfChannels;++i){
			sensorSimulatorPoller.start();
		}
		std::this_thread::sleep_for( duration );
	}
	
	return 0;
}
