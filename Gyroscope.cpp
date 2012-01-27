#include "Gyroscope.h"
#include "Logger.h"
#include "Singleton.h"

Gyroscope::Gyroscope(unsigned int port) 
{
	gyro(port); // Initialize gyro
	Singleton<Logger>::GetInstance().Logf("Starting Gyro on port %i", port);
}

Gyroscope::~Gyroscope() 
{
	Singleton<Logger>::GetInstance().Logf("Shutting down Gyro...");
}

double Gyroscope::GetOrientation()
{
	return gyro.GetAngle();
}

