

#include <ctime>
#include<vector>
#include <iostream>
#include "wirelessnetwork.h"
#include <queue>
#include "generator.h"
#include "simulator.h"

using std::vector;

int main()
{
	
	// Testing object creating
	UniformGenerator* root = new UniformGenerator(123);
	Simulator* test_simulator =new Simulator(root);

	Logger logger = Logger();
	logger.set_level(Logger::Level::Extra); // Info/Extra
	for(int i = 0 ; i < 10 ; i++)
	{
		test_simulator->simulation(500000, &logger, i+1,0.02);
	}

	return  0;
}
