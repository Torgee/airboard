

#include "RawDoubleSensorModule.h"


RawDoubleSensorModule::RawDoubleSensorModule
		(double value, msecs pollingInterval)
		 : value(value), polling_interval(polling_interval)
		// no need to set this here, will only be used after
		// initialization in 'start()'
		//stopASAP(false)
{
	
	// problematic, as 'this' pointer passed to thread construtor
	// is still incomplete at this point
	//  -> use 'start()' from outside afterwards
	// does work tho!
	start();
}


RawDoubleSensorModule::~RawDoubleSensorModule()
{
	// try-catch supposed not to be needed, cause
	// .join() will only throw when it's okay to destroy it
	// (have to check that again)
	//try{
	stop();
	//} catch (...) {
		
	//}
}


void RawDoubleSensorModule::setValue(double value)
{
	this->value = value;
}


// Note: 'stopASAP' is atomic<bool>!
void RawDoubleSensorModule::start()
{
	stopASAP = false;
	this->poll_thread = std::thread(&RawDoubleSensorModule::run,this);
}


// Note: 'stopASAP' is atomic<bool>!
void RawDoubleSensorModule::stop()
{
	stopASAP = true;
	
	// join() for now, we'll see if detach will work out later
	//this->poll_thread.detach();
	this->poll_thread.join();
}


// Note: 'stopASAP' is atomic<bool>!
void RawDoubleSensorModule::run()
{
	auto &pint = this->polling_interval;
	
	std::chrono::time_point<std::chrono::system_clock>
			last, now;
	
	
	
	last = std::chrono::system_clock::now();
	decltype(pint - (now - last)) duration;
	
	while(!stopASAP){
		publish(getValue());
		
		now = std::chrono::system_clock::now();
		duration = pint - (now - last);
		std::this_thread::sleep_for(duration);
		last = now;
	}
}


void RawDoubleSensorModule::publish(double) const
{
	//std::cout << "tid: " threadID << " - value: "
	//		<< getValue() << std::endl;
	std::cout << "sensor-value: " << getValue() << std::endl;
}


double RawDoubleSensorModule::getValue() const
{
	return this->value;
}
