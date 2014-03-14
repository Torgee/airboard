 
#ifndef ABSTRACTDATAGENERATOR_H
#define ABSTRACTDATAGENERATOR_H

// ToDo: rename that, cause it does not necessarily need to be a
// 'generator', could be a data reader as well - same interface
class AbstractDataGenerator {

public:
	AbstractDataGenerator();
	virtual ~AbstractDataGenerator();
	
	// eventually need a timestamp as parameter here!
	virtual getData() = 0;
	
private:

};

#endif // #ifndef ABSTRACTDATAGENERATOR_H
