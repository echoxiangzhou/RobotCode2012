#include "Display.h"
#include "DriveTrain.h"
#include "JoystickWrapper.h"
#include "Logger.h"
#include "Robot.h"
#include "Singleton.h"
#include "JoystickCallback.h"

Robot::Robot()
{
	Logger* logger = new Logger("/ni-rt/system/logs/robot.txt");
	Singleton<Display>::SetInstance(new Display);
	Singleton<Logger>::SetInstance(logger);
	Singleton<DriveTrain>::SetInstance(new DriveTrain);
	Singleton<Logger>::GetInstance().Logf("Starting the Robot class.");
	
	GetWatchdog().SetEnabled(false);
}

Robot::~Robot()
{
	Singleton<Logger>::GetInstance().Logf("Shutting down the Robot class.");
	
	//Destroy instances of singletons that we have used
	Singleton<Display>::DestroyInstance();
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
	JoystickWrapper joystick1(1, Attack3);
	JoystickWrapper joystick2(2, Attack3);
	
	Display& display = Singleton<Display>::GetInstance();
	DriveTrain& driveTrain = Singleton<DriveTrain>::GetInstance();
	
	JoystickCallback<Robot> jc(joystick1,this);
	jc.SetUpCallback(3,GET_FUNC(testCallbackUp));
	jc.SetDownCallback(3,GET_FUNC(testCallbackDown));
	jc.SetHeldCallback(3,GET_FUNC(testCallbackHeld));
	
	Singleton<Logger>::GetInstance().Logf("Starting operator control.");
	while( IsOperatorControl() )
	{
		float x, y;
		joystick1.GetAxis(&x, &y);
		
		display.Clear();
		display.PrintfLine(0, "Joystick: (%1.3f, %1.3f)", x, y);
		display.Update();
		jc.Update();
		
		driveTrain.DriveArcade(x, y);
//		Wait(0.01);
	}
	Singleton<Logger>::GetInstance().Logf("Stopping operator control.");
}

void Robot::testCallbackUp()
{
	Singleton<Display>::GetInstance().PrintfLine(1,"Up");
	Singleton<Logger>::GetInstance().Logf("Button 3 Up");
}

void Robot::testCallbackDown()
{
	Singleton<Display>::GetInstance().PrintfLine(1,"Down");
}

void Robot::testCallbackHeld()
{
	static int count = 0;
	Singleton<Display>::GetInstance().PrintfLine(2,"Held: %i",count++);
}

START_ROBOT_CLASS(Robot)
