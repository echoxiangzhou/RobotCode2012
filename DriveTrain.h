#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class DriveTrain
{
public:
	DriveTrain();
	~DriveTrain();
	
	void DriveArcade(double x, double y);
	void DriveTank(double left, double right);
};

#endif // DRIVETRAIN_H
