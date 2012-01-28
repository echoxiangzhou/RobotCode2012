#include "Display.h"
#include "DriveTrain.h"
#include "JoystickWrapper.h"
#include "Logger.h"
#include "Robot.h"
#include "Singleton.h"

Robot::Robot()
{
	Logger* logger = new Logger("log.txt");
	Singleton<Logger>::SetInstance(logger);
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
	JoystickWrapper joystick1(0, Attack3);
	JoystickWrapper joystick2(1, Attack3);
	
	Display& display = Singleton<Display>::GetInstance();
	DriveTrain& driveTrain = Singleton<DriveTrain>::GetInstance();
	
	Singleton<Logger>::GetInstance().Logf("Starting operator control.");
	while( IsOperatorControl() )
	{
		float x, y;
		joystick1.GetAxis(&x, &y);
		
		display.Clear();
		display.PrintfLine(0, "Joystick: (%3f, %3f)", x, y);
		display.Update();
		
		driveTrain.DriveArcade(x, y);
		Wait(0.01);
	}
	Singleton<Logger>::GetInstance().Logf("Stopping operator control.");
}

START_ROBOT_CLASS(Robot)
