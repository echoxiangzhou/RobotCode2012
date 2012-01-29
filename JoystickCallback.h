#ifndef JOYSTICKBUTTON_H
#define JOYSTICKBUTTON_H

#include "JoystickWrapper.h"
#include "Robot.h"
#include "Display.h"
#include "Singleton.h"

#define CALL_OBJECT_FUNC(member) (object->*(member))

template <class T>
class JoystickCallback
{
public:
	typedef void (T::*ObjectFuncPtr)(void);

	JoystickCallback(JoystickWrapper& joystick, T *object) :
		jwrapper(joystick),object(object)
		{
		Singleton<Display>::GetInstance().PrintfLine(1,"Joystick Callback constructed!");

		this->buttonCount = 12;
		this->downCallback = new ObjectFuncPtr[buttonCount];
		this->heldCallback = new ObjectFuncPtr[buttonCount];
		this->upCallback = new ObjectFuncPtr[buttonCount];
		this->buttonStates = new bool[buttonCount];
		for( int i = 0; i < buttonCount; i++ )
		{
			this->downCallback[i] = 0;
			this->heldCallback[i] = 0;
			this->upCallback[i] = 0;
			this->buttonStates[i] = false;
		}
		}

	~JoystickCallback()
	{
		Singleton<Display>::GetInstance().PrintfLine(1,"Woe is the Joystick Callback!");

		delete [] this->downCallback;
		delete [] this->heldCallback;
		delete [] this->upCallback;
		delete [] this->buttonStates;
	}

	void SetDownCallback(int button, ObjectFuncPtr fptr)
	{
		this->downCallback[button] = fptr;
	}

	void SetHeldCallback(int button, ObjectFuncPtr fptr)
	{
		this->heldCallback[button] = fptr;
	}

	void SetUpCallback(int button, ObjectFuncPtr fptr)
	{
		this->upCallback[button] = fptr;
	}

	void Update()
	{
		for( int i = 0; i < buttonCount; i++ )
		{
			bool state = this->buttonStates[i];
			this->buttonStates[i] = jwrapper.GetJoystick()->GetRawButton(i);
			if( state != this->buttonStates[i] )
			{
				if( state ) {
					if(upCallback[i] == NULL) continue;
					CALL_OBJECT_FUNC(upCallback[i])();
				} else {
					if(downCallback[i] == NULL) continue;
					CALL_OBJECT_FUNC(downCallback[i])();
				}
			}
			else if( state == 1 && this->buttonStates[i] == 1 )
			{
				if(heldCallback[i] == NULL) continue;
				CALL_OBJECT_FUNC(heldCallback[i])();
			}
		}
	}


private:
	JoystickWrapper& jwrapper;
	T *object;
	ObjectFuncPtr* downCallback;
	ObjectFuncPtr* heldCallback;
	ObjectFuncPtr* upCallback;
	bool* buttonStates;
	int buttonCount;
};

#endif // JOYSTICKBUTTON_H
