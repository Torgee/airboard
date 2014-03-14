 
#ifndef SENSORMODULE_H
#define SENSORMODULE_H

// wrappes sensor access, eventual data polling and the publishing
class SensorModule {

public:
	SensorModule(
		shared_ptr<AbstractActiveSensor> sensor,
		shared_ptr<AbstractPublisher> publisher)
		: sensor(sensor), publisher(publisher)
	{
		sensor.setCallback(this->dataCallback);
	}
		
	virtual ~SensorModule(){;}
	
	// don't know if that will be needed in the end, rather
	// start/stop the active sensor from outside(if thats possible)
	//void start();
	//void stop();
	
private:
	shared_ptr<ActiveSensor> sensor;
	shared_ptr<AbstractPublisher> publisher)
	
	void dataCallback(data)
	{
		publisher->publish(data);
	}
	
};

#endif // #ifndef SENSORMODULE_H
