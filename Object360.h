#include "WPIlib.h"

/* Some constants that define what buttons on the 360
 * map to what. */


class Object360 : public Joystick
{
	
public:
	/* Makes an instance of a new joystick that our
	 * 360 controller will use. Is in USB port 1.
	 * Has 6 axiseses and has 12 buttons (only 10
	 * buttons are actually on the 360 controller) */
	Object360(int);
	
	
	/* Easy functions to call to get the value of stuff. */
	bool GetA();
	bool GetB();
	bool GetX();
	bool GetY();
	bool GetRightBumper();
	bool GetLeftBumper();
	bool GetStart();
	bool GetSelect();
	bool GetLeftClick();
	bool GetRightClick();
	
	// (0,1] is right, [-1,0) is left. Range [-1,1]
	float GetLeftX();
	// (0,1] is down, [-1,0) is up. Range [-1,1] 
	float GetLeftY();
	/* Both triggers are in this. 
	 * Right Trigger is [-1,0]
	 * Left Trigger is [0,1]
	 * Return value = Right Trigger + Left Trigger */
	float GetTrigger();
	// (0,1] is right, [-1,0) is left. Range [-1,1]
	float GetRightX();
	// (0,1] is down, [-1,0) is up. Range [-1,1] 
	float GetRightY();

	/*get the axis state from the joystick class
	negative on x is left, positive is right
	negative on y is up, positive is down */
	float GetAxis(int);
	

};
