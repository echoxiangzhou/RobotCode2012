#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger
{
public:
	Logger(const std::string& fileName);
	~Logger();
	
	void Logf(const char* format, ...);
	
private:
	std::ofstream file;
};

#endif // LOGGER_H
