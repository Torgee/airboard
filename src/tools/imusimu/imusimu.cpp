
#include "IMUSimulator.h"


int main(int argc, char** argv)
{
	
	// ToDo: make program parameter for which kind of simulator to use!
	IMUSimulator &imusim = SimpleIMUSimulator();
	
	imusim.start();
	
	// ToDo: replace by proper waiting/interrupt
	int a;
	std::cin > a;
	
	imusim.stop();
	
	return 0;
