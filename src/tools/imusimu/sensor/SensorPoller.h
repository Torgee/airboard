 
#ifndef SENSORPOLLER_H
#define SENSORPOLLER_H

#include "AbstractActiveSensor.h"

class SensorPoller : public AbstractActiveSensor {

public:
	SensorPoller(shared_ptr<AbstractPassiveSensor> passiveSensor)
	{
		
		
	virtual ~SensorPoller()
	{
		this->stop();
		//int timeout = 100; // miliseconds
		//thread.wait_ms(timeout);
		//thread.terminate();
	}
	
	void setPollingInterval(std:chrono interval);
	
	void start()
	{
		// ToDo: remove!! for testing only!
		callbackFunction(passiveSensor->getData());
	}
	// stops after next poll
	void stop();
	
private:
	shared_ptr<AbstractPassiveSensor> passiveSensor;
	//Thread thread;

};

#endif // #ifndef SENSORPOLLER_H
