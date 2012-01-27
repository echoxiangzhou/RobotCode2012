#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <WPILib.h>

class Gyroscope 
{
public:
	Gyroscope(unsigned int port);
	~Gyroscope();
	
	double GetOrientation();
	
private:
	Gyro gyro;
};

#endif // GYROSCOPE_H
