#include <WPILib.h>
#include "Gyro.h"
#include "Logger.h"
#include "Singleton.h"

gyro::gyro(unsigned char port) {
	gyro(port); // Initialize gyro
	Singleton<Logger>::GetInstance().Logf("Starting Gyro on port %i", port);
}

gyro::~gyro() {
	
}

double gyro::getOrientation() {
	return double(g.GetAngle());
}

