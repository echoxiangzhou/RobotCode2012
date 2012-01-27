#ifndef ROBOT_H
#define ROBOT_H

#include <WPILib.h>

class Robot : public SimpleRobot
{
public:
	Robot();
	~Robot();
	
	void Autonomous();
	void OperatorControl();
};

#endif // ROBOT_H
