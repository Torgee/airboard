 
#ifndef RAWDOUBLESENSORMODULE_H
#define RAWDOUBLESENSORMODULE_H


#include <atomic>
#include <chrono>
#include <random>
#include <thread>


using msecs = std::chrono::milliseconds;

class RawDoubleActiveSensor {
	
};

class RawDoubleSensorModule {

public:
	RawDoubleSensorModule(double value, msecs polling_interval);
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
	
	void start();
	void stop();
	
	void run();
	void publish(double) const;
	
	double getValue() const;

};

#endif // #ifndef RAWDOUBLESENSORMODULE_H
