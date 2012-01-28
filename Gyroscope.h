#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <WPILib.h>

/**
 * Provides orientation information.
 */
class Gyroscope 
{
public:
	/**
	 * Constructor.
	 * 
	 * \param port the port that the gyro is on.
	 */
	Gyroscope(unsigned int port);
	
	/**
	 * Destructor.
	 */
	~Gyroscope();
	
	/**
	 * Get the orientation information from the Gyro (in degrees).
	 */
	double GetOrientation();
	
	/**
	 * Set the current orientation as zero.
	 */
	void Reset();
	
private:
	Gyro gyro;
};

#endif // GYROSCOPE_H
