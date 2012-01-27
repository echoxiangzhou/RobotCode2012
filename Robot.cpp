#include "DriveTrain.h"
#include "Logger.h"
#include "Robot.h"
#include "Singleton.h"

Robot::Robot()
{
	Singleton<Logger>::GetInstance().Logf("Starting the Robot class.");
}

Robot::~Robot()
{
	Singleton<Logger>::GetInstance().Logf("Shutting down the Robot class.");
	
	//Destroy instances of singletons that we have used
	Singleton<DriveTrain>::DestroyInstance();
	Singleton<Logger>::DestroyInstance();
}

void Robot::Autonomous()
{
	Singleton<Logger>::GetInstance().Logf("Starting Autonomous Mode.");
	while ( IsAutonomous() )
	{
		///\todo Implement this!
		Wait(0.01);
	}
	Singleton<Logger>::GetInstance().Logf("Stopping Autonomous Mode.");
}

void Robot::OperatorControl()
{
	Singleton<Logger>::GetInstance().Logf("Starting operator control.");
	while( IsOperatorControl() )
	{
		Wait(0.01);
	}
	Singleton<Logger>::GetInstance().Logf("Stopping operator control.");
}

START_ROBOT_CLASS(Robot)
