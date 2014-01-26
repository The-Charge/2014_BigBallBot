#include "Object360.h"
const short BUTTON_A_ID = 1;
const short BUTTON_B_ID = 2;
const short BUTTON_X_ID = 3;
const short BUTTON_Y_ID = 4;
const short BUTTON_LEFT_BUMPER_ID = 5;
const short BUTTON_RIGHT_BUTTON_ID = 6;
const short BUTTON_SELECT_ID = 7;
const short BUTTON_START_ID = 8;
const short BUTTON_LEFT_CLICK_ID = 9;
const short BUTTON_RIGHT_CLICK_ID = 10;

const short AXIS_LEFT_X_ID = 1;
const short AXIS_LEFT_Y_ID = 2;
const short AXIS_TRIGGER_ID = 3;
const short AXIS_RIGHT_X_ID = 4;
const short AXIS_RIGHT_Y_ID = 5;

Object360::Object360(int port):Joystick(port,6,12)
{
	
}
bool Object360::GetA()
{ 
	return GetRawButton(BUTTON_A_ID); 
}

bool Object360::GetB()
{ 
	return GetRawButton(BUTTON_B_ID); 
}
bool Object360::GetX()
{ 
	return GetRawButton(BUTTON_X_ID); 
}
bool Object360::GetY()
{ 
	return GetRawButton(BUTTON_Y_ID); 
}
bool Object360::GetRightBumper()
{ 
	return GetRawButton(BUTTON_RIGHT_BUTTON_ID); 
}
bool Object360::GetLeftBumper()
{ 
	return GetRawButton(BUTTON_LEFT_BUMPER_ID); 
}
bool Object360::GetStart()
{ 
	return GetRawButton(BUTTON_START_ID); 
}
bool Object360::GetSelect()
{ 
	return GetRawButton(BUTTON_SELECT_ID); 
}
bool Object360::GetLeftClick()
{ 
	return GetRawButton(BUTTON_LEFT_CLICK_ID); 
}
bool Object360::GetRightClick()
{ 
	return GetRawButton(BUTTON_RIGHT_CLICK_ID); 
}

float Object360::GetLeftX() 
{ 
	return GetAxis(AXIS_LEFT_X_ID); 
} 
float Object360::GetLeftY() 
{ 
	return GetAxis(AXIS_LEFT_Y_ID); 
}
float Object360::GetTrigger() 
{ 
	return GetAxis(AXIS_TRIGGER_ID); 
}	
float Object360::GetRightX() 
{ 
	return GetAxis(AXIS_RIGHT_X_ID); 
}
float Object360::GetRightY() 
{ 
	return GetAxis(AXIS_RIGHT_Y_ID); 
}


float Object360::GetAxis(int axis)
{
	return GetRawAxis(axis);
}
