 
#ifndef ABSTRACTPUBLISHER_H
#define ABSTRACTPUBLISHER_H

// this class is used as an interface to allow multipe implementations
// for publishing e.g. sensor data

// use variable template list here
template<classname ...>
class AbstractPublisher {

public:
	AbstractPublisher(){;}
	virtual ~AbstractPublisher(){;}
	
	virtual void publish(double) = 0;
	
private:

};

#endif // #ifndef ABSTRACTPUBLISHER_H
