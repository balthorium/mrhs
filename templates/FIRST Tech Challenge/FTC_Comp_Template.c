
// Flag to control whether "test mode" (i.e. autonomous only) or "competition" mode
// 1. For testing user control mode only leave the code as follows.
// 2. For real competition, remove the "#define bUserControlTestModeOnly" or comment it out.
// This will allow you to use the mini-joystick application builtin the ROBOTC application for testing
// user control.
#define bUserControlTestModeOnly



#include "FTC_Comp_Include.c"

void Initialization()
{
   nxtDisplayTextLine(2, "Initialization");
}

task Autonomous()
{
   nxtDisplayTextLine(2, "Autonomous");
}

task Human_Control()
{
	while(true)
	{
    nxtDisplayTextLine(2, "Human_Control");
		wait1Msec(5);
	}
}
