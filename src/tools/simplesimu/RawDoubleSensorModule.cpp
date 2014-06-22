

#include "RawDoubleSensorModule.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

RawDoubleSensorModule::RawDoubleSensorModule(
		double value,
		msecs pollingInterval,
		zmq::context_t &context)
		 : 
		m_value(value),
		m_pollingInterval(pollingInterval),
		m_pub_socket(context, ZMQ_PUB)
		// no need to set this here, will only be used after
		// initialization in 'start()'
		//stopASAP(false)
{
	
	// try High Water Mark
	m_pub_socket.setsockopt(ZMQ_SNDHWM,1)
	
	// bind to ipc channel
	// ToDo: get the channel per parameter, or preferably, get the
	// whole publishing functionality in a dedicated class
	m_pub_socket.bind("tcp://*:5556");
	//m_pub_socket.connect("tcp://*:5556");
    m_pub_socket.bind("ipc:///tmp/sensor.ipc");
    
	
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


// Note: 'm_stopASAP' is atomic<bool>!
void RawDoubleSensorModule::run()
{
	auto &pint = this->m_pollingInterval;
	
	std::cout << "(in run:) polling interval: "
		<< std::chrono::duration_cast<msecs>(pint).count()
		<< "msecs" << std::endl;
	
	//std::chrono::time_point<std::chrono::system_clock>
			//last, now;
			
	// didn't work like this ... just compensate for the time
	// it took to actually publish
	//auto last = std::chrono::system_clock::now();
	//decltype(last) now;
	
	//decltype(pint - (now - last)) duration;
	
	decltype(std::chrono::system_clock::now()) pre, post;	
	
	//last = std::chrono::system_clock::now();
	decltype(pint - (pre - post)) duration;
	
	while(!m_stopASAP){
		
		pre = std::chrono::system_clock::now();
		publish(getValue());
		post = std::chrono::system_clock::now();
		
		duration = pint - (pre - post);
		
		//now = std::chrono::system_clock::now();
		//duration = pint - (now - last);
		std::this_thread::sleep_for(duration);
		//std::cout << "time slept: "
				//<< std::chrono::duration_cast<msecs>(duration).count()
				//<< "msecs" << std::endl;
		
		//last = now;
	}
}


void RawDoubleSensorModule::publish(double value)
{
	//static_assert(false,"needs to be changed to using zeromq!");
	
	// grab the value and put it on the message
	// Note: seems like a new message-obejct needs to be created for
	//       every send
	// Note: (obsolete by previous note!) possibly one could create a
	// double* to the same address as m_message.data, to avoid repeated
	// casts, even though the compiler might optimize that anyway
	// Serious! Note: don't forget to switch to protobuf or similar!!!
	
	
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto ms_epoch = std::chrono::duration_cast<msecs>(now).count();
    
    m_rawDouble.set_timestamp(ms_epoch);
	//double value = getValue();
	m_rawDouble.set_value(value);
	
	//zmq::message_t message(sizeof(double));
	//*(static_cast<double*>(message.data())) = getValue();
	auto buffer_size = m_rawDouble.ByteSize();
	zmq::message_t message(buffer_size);
	
	m_rawDouble.SerializeToArray(message.data(),buffer_size);
	
	RawDouble dub;
	//dub.ParseFromString(buffer);
	dub.ParseFromArray(message.data(),buffer_size);
	
#ifdef VERBOSE
	std::cout << "****" << std::endl;
	//auto now = std::chrono::system_clock::now();
	//auto the_time = std::chrono::system_clock::to_time_t(now);
	//std::cout << "ts: " << std::ctime(std::localtime(&the_time),"%T");
	//std::cout << "ts: " << std::ctime(&the_time) << std::endl;
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto ms_epoch = std::chrono::duration_cast<msecs>(now).count();
	std::cout << "ts: " << ms_epoch << std::endl;
	std::cout << "value: " << value << std::endl;
	std::cout << "RawDouble: " << m_rawDouble.value() << std::endl;
	std::cout << "re-parsed: " << dub.value() << std::endl;
	std::cout << "buff_len: " << buffer_size << std::endl;
	std::cout << "message: '"
			<< std::string(static_cast<char*>(message.data()))
			<< "'" << std::endl;
#endif // #ifdef VERBOSE
	
	//std::cout << "sending sensor-value: "
			//<< *(static_cast<double*>(message.data()))
			//<< std::endl;
			
	m_pub_socket.send(message);
}


double RawDoubleSensorModule::getValue() const
{
	return this->m_value;
}
