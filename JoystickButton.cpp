#include "JoystickButton.h"
#include "JoystickWrapper.h"

JoystickButton::JoystickButton(JoystickWrapper& joystick) :
	jwrapper(joystick)
{
	this->buttonCount = 12;
	this->downCallback = new RobotFuncPtr[buttonCount];
	this->heldCallback = new RobotFuncPtr[buttonCount];
	this->upCallback = new RobotFuncPtr[buttonCount];
	this->buttonStates = new bool[buttonCount];
	for( int i = 0; i < buttonCount; i++ )
	{
		this->downCallback[i] = 0;
		this->heldCallback[i] = 0;
		this->upCallback[i] = 0;
		this->buttonStates[i] = false;
	}
}

JoystickButton::~JoystickButton()
{
	delete [] this->downCallback;
	delete [] this->heldCallback;
	delete [] this->upCallback;
	delete [] this->buttonStates;
}

void JoystickButton::SetDownCallback(int button, RobotFuncPtr fptr)
{
	this->downCallback[button] = fptr;
}

void JoystickButton::SetHeldCallback(int button, RobotFuncPtr fptr)
{
	this->heldCallback[button] = fptr;
}

void JoystickButton::SetUpCallback(int button, RobotFuncPtr fptr)
{
	this->upCallback[button] = fptr;
}

void JoystickButton::Update()
{
	for( int i = 0; i < buttonCount; i++ )
	{
		bool state = this->buttonStates[i];
		this->buttonStates[i] = jwrapper.GetJoystick()->GetRawButton(i);
		if( state != this->buttonStates[i] )
		{
			if( state )
				this->upCallback[i]();
			else
				this->downCallback[i]();
		}
		else if( state == 1 && this->buttonStates[i] == 1 )
		{
			this->heldCallback[i]();
		}
	}
}
