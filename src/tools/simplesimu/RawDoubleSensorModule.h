 
#ifndef RAWDOUBLESENSORMODULE_H
#define RAWDOUBLESENSORMODULE_H


#include <atomic>
#include <chrono>
#include <random>
#include <thread>

#include "zmq.hpp"


using msecs = std::chrono::milliseconds;

class RawDoubleActiveSensor {
	
};

class RawDoubleSensorModule {

public:
	RawDoubleSensorModule(double value, msecs polling_interval,
			zmq::context_t &context);
	virtual ~RawDoubleSensorModule();
	
	static constexpr double DEFAULT_VALUE = 0.0;
	static constexpr msecs DEFAULT_INTERVAL = msecs(100);

	void setValue(double value);
	//void setPollingInverval(dur duration);
	
	
private:
	std::atomic<double> m_value;
	msecs m_pollingInterval;
	
	std::thread m_pollThread;
	// stop the thread As Soon As Possible
	std::atomic<bool> m_stopASAP;
	
	// will be initialized and bound in c'tor
	zmq::socket_t m_pub_socket;
	
	void start();
	void stop();
	
	void run();
	// probalby, constness needs to be removed when using e.g. zeromq,
	// as the zmq publishing class will probalbly not work as const
	void publish(double);
	
	double getValue() const;

};

#endif // #ifndef RAWDOUBLESENSORMODULE_H
