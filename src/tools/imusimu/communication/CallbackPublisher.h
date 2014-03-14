 
#ifndef CALLBACKPUBLISHER_H
#define CALLBACKPUBLISHER_H

#include "AbstractPublisher.h"

class CallbackPublisher : public AbstractPublisher {

public:
	CallbackPublisher(void pubfunc(data)) : pubfunc(pubfunc)
	{
		;
	}
	
	virtual ~CallbackPublisher()
	{
		;
	}
	
	void setPubFunc(void pubfunc(double))
	{
		this->pubfunc = pubfunc;
	}
	
	void publish(double data)
	{
		pubfunc(data);
	}
	
private:
	void pubfunc(double);

};

#endif // #ifndef CALLBACKPUBLISHER_H
