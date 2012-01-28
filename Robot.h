#ifndef ROBOT_H
#define ROBOT_H

#include <WPILib.h>

/**
 * Our main robot class.
 */
class Robot : public SimpleRobot
{
public:
	/**
	 * Constructor.
	 */
	Robot();
	
	/**
	 * Destructor.
	 */
	~Robot();
	
	/**
	 * Method for operations during autonomous mode.
	 */
	void Autonomous();
	
	/**
	 * Method for teleop mode.
	 */
	void OperatorControl();
};

#endif // ROBOT_H
