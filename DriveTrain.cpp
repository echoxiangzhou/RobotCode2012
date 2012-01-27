#include "DriveTrain.h"
#include "Logger.h"
#include "Singleton.h"

DriveTrain::DriveTrain()
{
	Singleton<Logger>::GetInstance().Logf("DriveTrain() initializing.");
}

DriveTrain::~DriveTrain()
{
	Singleton<Logger>::GetInstance().Logf("~DriveTrain() stopping.");
}

void DriveTrain::DriveArcade(double x, double y)
{
}

void DriveTrain::DriveTank(double left, double right)
{
}
