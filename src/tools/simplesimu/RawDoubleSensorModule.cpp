

#include "RawDoubleSensorModule.h"

#include <iostream>

RawDoubleSensorModule::RawDoubleSensorModule
		(double value, msecs pollingInterval)
		 : m_value(value), m_pollingInterval(pollingInterval)
		// no need to set this here, will only be used after
		// initialization in 'start()'
		//stopASAP(false)
{
	
	// problematic, as 'this' pointer passed to thread constructor
	// is still incomplete at this point
	// solution would be to use 'start()' from outside afterwards
	// still does work like this, as 'start()' is the last statement
	// (AFAIK that's the reason it's working)
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
	this->m_value = value;
}


// Note: 'stopASAP' is atomic<bool>!
void RawDoubleSensorModule::start()
{
	m_stopASAP = false;
	this->m_pollThread = std::thread(&RawDoubleSensorModule::run,this);
}


// Note: 'm_stopASAP' is atomic<bool>!
void RawDoubleSensorModule::stop()
{
	m_stopASAP = true;
	
	// join() for now, we'll see if detach will work out later
	//this->poll_thread.detach();
	this->m_pollThread.join();
}


// Note: 'stopASAP' is atomic<bool>!
void RawDoubleSensorModule::run()
{
	auto &pint = this->m_pollingInterval;
	
	std::cout << "(in run:) polling interval: "
		<< std::chrono::duration_cast<msecs>(pint).count()
		<< "msecs" << std::endl;
	
	//std::chrono::time_point<std::chrono::system_clock>
			//last, now;
			
	auto last = std::chrono::system_clock::now();
	decltype(last) now;
	
	
	//last = std::chrono::system_clock::now();
	decltype(pint - (now - last)) duration;
	
	while(!m_stopASAP){
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
	return this->m_value;
}
