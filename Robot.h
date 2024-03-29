#ifndef ROBOT_H
#define ROBOT_H

#include <WPILib.h>
#define GET_FUNC(x) &Robot::x

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
	
private:
	void testCallbackUp();
	void testCallbackDown();
	void testCallbackHeld();
};

#endif // ROBOT_H
