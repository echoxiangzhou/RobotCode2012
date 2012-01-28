#include <cstdarg>
#include <cstdio>
#include <ctime>

#include "Logger.h"

using std::clock;
using std::endl;
using std::string;

Logger::Logger(const string& fileName)
{
	this->file.open(fileName);
}

Logger::~Logger()
{
	this->file.close();
}

void Logger::Logf(const char* format, ...)
{
	va_list args;
	va_start(format, args);
	char buffer[256];
	vsprintf(buffer, 255, format, args);
	va_end(args);
	
	//Create a timestamp
	char message[300];
	double time = (double)clock() / (double)CLOCKS_PER_SEC;
	sprintf(message, "[%f] %s", time, buffer);
	
	this->file << message << endl;
}
