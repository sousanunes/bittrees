#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <iostream>

class Logger
{
private:
	static std::string printTime()
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime( & t );
		std::string output;
		output += "[";
	    output += std::to_string(now->tm_year + 1900) + "-";
	    output += std::to_string(now->tm_mon + 1) + "-";
	    output += std::to_string(now->tm_mday) + " ";
	    output += std::to_string(now->tm_hour) + ":";
	    output += std::to_string(now->tm_min)  + ":";
	    output += std::to_string(now->tm_sec);
	    output += "] ";
		return output;
	}

public:
	static void log(std::string suffix)
	{
		std::cout << "\033[32m" << suffix << " " << "\033[0m" << std::flush;
	}

	static void info(std::string suffix)
	{
		std::string output = Logger::printTime() + suffix;
		std::cout << "\033[32m" << output << "\033[0m" << std::endl;
	}

	static void print(std::string suffix)
	{
		std::string output = Logger::printTime() + suffix;
		std::cout << "\033[32m" << output << "\033[0m" << std::endl;
	}

	static void printNoNewLine(std::string suffix)
	{
		std::string output = Logger::printTime() + suffix;
		std::cout << "\033[32m" << output << "\033[0m" << std::flush;
		;
	}

	static void warn(std::string suffix)
	{
		std::string output = Logger::printTime() + "WARNING: " + suffix;
		std::cout << "\033[33m" << output << "\033[0m" << std::endl;
	}

	static void error(std::string suffix)
	{
		std::string output = Logger::printTime() + "ERROR: " + suffix;
		std::cout << "\033[1;31m" << output << "\033[0m" << std::endl;
	}

};

#endif