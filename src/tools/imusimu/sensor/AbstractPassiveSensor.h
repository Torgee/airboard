 
#ifndef ABSTRACTPASSIVESENSOR_H
#define ABSTRACTPASSIVESENSOR_H

class AbstractPassiveSensor {

public:
	AbstractPassiveSensor();
	virtual ~AbstractPassiveSensor();
	
	virtual getData() = 0;
	
private:

};

#endif // #ifndef ABSTRACTPASSIVESENSOR_H
