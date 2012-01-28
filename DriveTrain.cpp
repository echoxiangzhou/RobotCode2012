#include <WPILib.h>

#include "DriveTrain.h"
#include "Logger.h"
#include "Singleton.h"

int round(float d, int pos = 1);

DriveTrain::DriveTrain()
{
	Singleton<Logger>::GetInstance().Logf("DriveTrain() initializing.");

	this->left = new Jaguar(1, 1);
	this->right = new Jaguar(1, 2);
}

DriveTrain::~DriveTrain()
{
	Singleton<Logger>::GetInstance().Logf("~DriveTrain() stopping.");
	
	delete this->left;
	delete this->right;
}

void DriveTrain::DriveArcade(double x, double y)
{
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
}

void DriveTrain::DriveTank(double left, double right)
{
	left->Set(left);
    right->Set(right);
}

int round(float d, int pos = 1) {
	if (d - floor(d) >= .5) return ceil(d);
	return floor(d);
}
