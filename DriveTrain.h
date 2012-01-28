#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class Jaguar;

/**
 * The drivetrain of our Robot. Can be driven arcade-style with a single joystick or tank-drive with two joysticks.
 */
class DriveTrain
{
public:
	/**
	 * Constructor.
	 */
	DriveTrain();
	
	/**
	 * Destructor.
	 */
	~DriveTrain();
	
	/**
	 * Drive arcade-style with a single joystick.
	 * 
	 * \param x the value of the x channel of the joystick.
	 * \param y the value of the y channel of the joystick.
	 */
	void DriveArcade(double x, double y);
	
	/**
	 * Drive tank-style with two channels.
	 * 
	 * \param left the left wheel channel.
	 * \param right the right wheel channel.
	 */
	void DriveTank(double left, double right);
	
private:
	Jaguar* left;
	Jaguar* right;
};

#endif // DRIVETRAIN_H
