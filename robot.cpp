#include "robot.h"
#include <time.h>

//#define ARCADEDRIVE
//#define INTUITDRIVE
#define TANKDRIVE

Team2502_TankTest::Team2502_TankTest()
{
    left = new Jaguar(1, 1);
    right = new Jaguar(1, 2);
    
#ifdef TANKDRIVE
    joyLeft = new JoystickWrapper(1, Attack3);
    joyRight = new JoystickWrapper(2, Attack3);
#else
#ifdef ARCADEDRIVE
    joyLeft = new JoystickWrapper(1, Extreme3DPro);
    joyRight = NULL;

#else
#ifdef INTUITDRIVE
    joyLeft = new JoystickWrapper(1, Extreme3DPro);
    joyRight = NULL;
#else
#error You must define either tank drive or arcade drive
#endif
#endif
#endif
}

Team2502_TankTest::~Team2502_TankTest()
{
    delete left;
    delete right;
    delete joyLeft;
    delete joyRight;
}

void Team2502_TankTest::OperatorControl()
{
	Gyro gyro(1);
	gyro.Reset();
	dstation = DriverStationLCD::GetInstance();
	int toggle_trigger = 0;
	while(IsOperatorControl()) {
        if (joyLeft != NULL && joyLeft->joystick->GetTrigger() == true) {
        	left->Set(0);
        	right->Set(0);
        	toggle_trigger = 1;
        	continue;
        } else if (joyRight != NULL && joyRight->joystick->GetTrigger() == true) {
        	left->Set(0);
        	right->Set(0);
        	toggle_trigger = 1;
        	continue;
        }
        while (toggle_trigger == 1 && (joyRight->joystick->GetTrigger() == false || joyLeft->joystick->GetTrigger() == false)) Wait(0.01);
        toggle_trigger = 0;
#ifdef TANKDRIVE
        float x,y;
        joyLeft->GetAxis(&x,&y);
        float x2,y2;
        joyRight->GetAxis(&x2,&y2);
        dstation->PrintfLine(DriverStationLCD::kUser_Line2, "%f", y);
        dstation->PrintfLine(DriverStationLCD::kUser_Line3, "%f", y2);
        dstation->PrintfLine(DriverStationLCD::kUser_Line4, "%f", left->Get());
        DriveTank(-y,y2); // Switched (y,y2) to (-y,y2) so that it drives
#endif
#ifdef ARCADEDRIVE
        float x,y;
        joyLeft->GetAxis(&x,&y);
        dstation->PrintfLine(DriverStationLCD::kUser_Line2, "%f", x);
        dstation->PrintfLine(DriverStationLCD::kUser_Line3, "%f", y);
        DriveArcade(x, y, gyro.GetAngle());
#endif
        dstation->PrintfLine(DriverStationLCD::kUser_Line1, "%f", gyro.GetAngle());
        dstation->UpdateLCD();
        Wait(0.01);
    }
}

void Team2502_TankTest::DriveTank(float __left, float __right)
{
    left->Set(__left);
    right->Set(__right);
    
}

int round(float d, int pos);

void Team2502_TankTest::DriveArcade(float x, float y, float gyro) {
	//left->Set(-(y-x));
	//right->Set(y+x);
	/*
	Quad 1: ((x*45) - (y*45)) + 45
	Quad 2: 0 - ((x*45) + (y*45)) - 135)
	Quad 3: ((0-x)*45)-((0-y)*45) + 225
	Quad 4: 0 - (((0-x)*45) + ((0-y)*45) - 315)
	*/
	float angle = 0.00;
	float sens = .2;
			if (x >= sens && y >= sens) { 				// Quad 1
														angle = ((x*45) - (y*45)) + 45;
	} else 	if (x >= sens && y <= sens) { 				// Quad 2
														angle = 0 - (((x*45) + (y*45)) - 135);
	} else 	if (x <= sens && y <= sens) {				// Quad 3
														angle = ((0-x)*45)-((0-y)*45) + 225;
	} else 	if (x <= sens && y >= sens) {				// Quad 4
														angle = 0 - (((0-x)*45) + ((0-y)*45) - 315);
	}
	/* Translate Gyro angle into human-readable form */
	if (gyro < 0) {
		gyro = 0 - gyro;
		gyro = 360 - gyro;
		gyro = round(gyro, 1) % 360;
	} else {
		gyro = round(gyro, 1) % 360;
	}
	float turn = 0.00;
	int sturn = 0; // Default - Still
	// Calculate Smallest Turn Angle
	float turn1 = 0.00; // Up, through zero
	float turn2 = 0.00; // Down, through 180
	turn1 = angle + (360 - gyro);
	turn2 = gyro - angle;
	if (turn1 < turn2 && turn1 >= 0) {
		turn = turn1;
		sturn = 1; // Right
	} else if (turn2 < turn1 && turn2 >= 0) {
		turn = turn2;
		sturn = -1; // Left
	} else if (turn1 == turn2) {
		turn = turn1;
		sturn = -1; // Left - Random
	} else {
		// ?! Don't Turn !?
	}
	// Override turn
	if (turn <= 15 && turn >= -15) {
		sturn = 0;
	}
	// Spin Motor Speeds according to sturn
	float sensX = x;
	if (sensX < 0) sensX = 0 - sensX;
	dstation->PrintfLine(DriverStationLCD::kUser_Line4, "%i", sturn);
	dstation->PrintfLine(DriverStationLCD::kUser_Line5, "%f", angle);
	dstation->PrintfLine(DriverStationLCD::kUser_Line6, "%f", turn2);
	if (sturn == -1) {
		left->Set(.5);
		right->Set(-.5);
	} else if (sturn == 1) {
		left->Set(-.5);
		right->Set(.5);
	} else {
		left->Set(-(y-x));
		right->Set(y+x);
	}
}

int round(float d, int pos = 1) {
	if (d - floor(d) >= .5) return ceil(d);
	return floor(d);
}

START_ROBOT_CLASS(Team2502_TankTest)
