#include "logger.h"


#include <fstream>
#include <iostream>
#include <string>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Info(std::string message)
{


	if (level_ != Level::Error)
	{
		/*std::ofstream foutput;
		std::ifstream finput;
		finput.open("logger.txt");
		foutput.open("logger.txt", std::ios::app);
		std::string log = "[Info] " + message + "\n";
		if (finput.is_open())
			foutput << log;

		finput.close();
		foutput.close();
		
		std::cout << "[Info] " << message << std::endl;*/
	}
}

void Logger::Extra(std::string message)
{

if (level_ != Level::Info && level_ != Level::Error)
	{
		/*std::ofstream foutput;
		std::ifstream finput;
		finput.open("logger.txt");
		foutput.open("logger.txt", std::ios::app);
		std::string log = "[Extra] " + message + "\n";
		if (finput.is_open())
			foutput << log;

		finput.close();
		foutput.close();

		std::cout << "[Extra] " << message << std::endl;*/
		
	}
	
}

void Logger::Error(std::string message)
{
	
	/* std::ofstream foutput;
	std::ifstream finput;
	finput.open("logger.txt");
	foutput.open("logger.txt", std::ios::app);
	std::string log = "[Error] " + message + "\n";
	if (finput.is_open())
		foutput << log;

	finput.close();
	foutput.close();
	
	std::cout << "[Error] " << message << std::endl;*/
	 
}
