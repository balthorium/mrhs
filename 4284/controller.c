#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,      ,             tmotorTetrix, openLoop)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "JoystickDriver.c"


task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		motor[mtr_S1_C1_1] = joystick.joy1_x1;
		motor[mtr_S1_C1_2] = joystick.joy2_x1;
	}
}
