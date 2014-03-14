 
#ifndef PASSIVESENSORSIMULATOR_H
#define PASSIVESENSORSIMULATOR_H


#include <random>

#include "sensor/AbstractPassiveSensor.h"

class PassiveRandomSensorSimulator : public AbstractPassiveSensor {

public:
	PassiveSensorSimulator(double low, double high) :
			low(low), high(high)
	{
		;
	}
	
	virtual ~PassiveSensorSimulator()
	{
		;
	}
	
	virtual double getData()
	{
		return low+(high-low)*rand();
	}
	
private:
	double low,high;

};

#endif // #ifndef PASSIVESENSORSIMULATOR_H
