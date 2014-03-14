 
#ifndef ABSTRACTACTIVESENSOR_H
#define ABSTRACTACTIVESENSOR_H

class AbstractActiveSensor {

public:
	
	void setCallback(void callbackFunction(double));
	
protected:
	AbstractActiveSensor();
	virtual ~AbstractActiveSensor();
	
	void callbackFunction(double);
	
private:

};

#endif // #ifndef ABSTRACTACTIVESENSOR_H
