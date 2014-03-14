 
#ifndef STATICDATAGENERATOR_H
#define STATICDATAGENERATOR_H

template<typename T>
class StaticDataGenerator {

public:
	StaticDataGenerator(T value) : value(value)
	{
		;
	}
	virtual ~StaticDataGenerator();
	
	void setValue(T value)
	{
		this->value = value;
	}
	
	// ToDo: check if there is a better return type, e.g. T&& or so
	T getValue()
	{
		return value;
	}
	
	
private:
	T value;

};

#endif // #ifndef STATICDATAGENERATOR_H
