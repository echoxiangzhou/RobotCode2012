#include <cstdarg>
#include <cstdio>

#include "Logger.h"

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
	this->file << buffer << endl;
}
