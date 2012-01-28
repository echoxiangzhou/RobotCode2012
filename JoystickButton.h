#ifndef JOYSTICKBUTTON_H
#define JOYSTICKBUTTON_H

class JoystickWrapper;
class Robot;

class JoystickButton
{
public:
	typedef void (Robot::*funcPtr)(void) RobotFuncPtr;
	
	JoystickButton(JoystickWrapper& joystick);
	~JoystickButton();
	
	void SetDownCallback(int button, RobotFuncPtr fptr);
	void SetHeldCallback(int button, RobotFuncPtr fptr);
	void SetUpCallback(int button, RobotFuncPtr fptr);
	void Update();
	
private:
	JoystickWrapper& jwrapper;
	RobotFuncPtr* downCallback;
	RobotFuncPtr* heldCallback;
	RobotFuncPtr* upCallback;
	bool* buttonStates;
	int buttonCount;
};

#endif // JOYSTICKBUTTON_H
