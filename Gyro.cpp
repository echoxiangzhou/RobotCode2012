#include <WPILib.h>
#include "Gyro.h"
#include "Logger.h"

gyro::gyro(unsigned char port) {
	gyro(port); // Initialize gyro
}

gyro::~gyro() {
	
}

double gyro::getOrientation() {
	return double(g.GetAngle());
}

