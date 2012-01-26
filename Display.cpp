#include <WPILib.h>
#include <cstdarg>
#include "Display.h"

Display::Display {
	dstation = DriverStationLCD::GetInstance();
}

Display::~Display {
	
}

void Display::Printf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	char buf[256];
	vsnprintf(buf, 255, format, args);
	va_end(args);
}
