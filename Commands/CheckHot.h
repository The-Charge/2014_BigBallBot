#ifndef CHECK_HOT_H
#define CHECK_HOT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"
 
class CheckHot: public Command {
		
	
public:
	CheckHot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
