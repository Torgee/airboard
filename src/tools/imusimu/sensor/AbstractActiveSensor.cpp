

#include "AbstractActiveSensor"


AbstractActiveSensor::AbstractActiveSensor()
{
	;
}


AbstractActiveSensor::~AbstractActiveSensor()
{
	;
}


void AbstractActiveSensor::setCallback(void callbackFunction(double))
{
	this->callbackFunction = callbackFunction;
}
