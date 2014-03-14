 
#ifndef IPCPUBLISHER_H
#define IPCPUBLISHER_H

#include <iostream>

#include "AbstractPublisher.h"

class IPCPublisher : AbstractPublisher {

public:
	IPCPublisher();
	virtual ~IPCPublisher();
	
	virtual void publish(double data)
	{
		std::cout << "pub: " << data << std::endl;
	}
	
private:
	// params
};

#endif // #ifndef IPCPUBLISHER_H
