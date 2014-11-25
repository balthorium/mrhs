#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  motorA,          ,              tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     controlMotor,  tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     ,              tmotorNone, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

////////////////////////////////////////////////////////////////////////////////////////////////
//
//                        FTC Hitechnic Motor Latency Test Program
//
// A program to test the "latency" of the HiTechnic Motor Controller. Ltency is the time from
// when the user program commands the firmware to set the motor power until the change is reflected
// by motor movement.
//
// The test arrangement is as follows:
// 1. A standard NXT motor is connected to NXT motor port A.
//
// Various tests were performed on the motor to measure the latency. These include:
// 1. How long it took from a stopped position before the motor started moving.
// 2. How long it took from moving forward to reverse the motor. That is, if it was moving forward
//    at power level "X" and power level was changed to "-X", how long it took before the
//    encoder change direction changed to a negative increment.
// 3. Above two experiments were measured with a variety of power levels.
//
// Simply compile and download this program. Make sure the debugger "NXT Devices" window is
// open and the debugger is set for "Continuous" polling.
//
// NOw run the program and watch the debugger window. Make sure the appropriate encoder values
// are properly changed.
//    -- They should increase for forward (positive) power. And decrease for reverse (negative)
//       motor power.
//    -- The encoder values that change should correspond to the motor that is powered. Otherwise
//       the encoders are wired to the wrong ports.
//
////////////////////////////////////////////////////////////////////////////////////////////////

const tMotor encoderPort = controlMotor;

task main()
{
	// Stop both motors

	int nCycles = 0;
	int nPowerLevel = 100;

	long nStartTimeMin = 9999;
	long nStartTimeAvg;
	long nStartTimeMax = 0;

	long nFlipTimeMin = 9999;
	long nFlipTimeAvg;
	long nFlipTimeMax = 0;

	long nBrakeTimeMin = 9999;
	long nBrakeTimeAvg;
	long nBrakeTimeMax = 0;

	long nBrakeTime;
	long nStartTime;
	long nFlipTime;

	long nStartTimeSum   = 0;
	long nFlipTimeSum    = 0;
	long nBrakeTimeSum   = 0;

	long nLastControlEncoder     = 0;

	muxLowBatteryShutdown = 5000;
	for (nCycles = 1; true; ++nCycles)
	{

		// Stop both motors

		motor[controlMotor]   = 0;

		// Make sure they are both stopped

		while (true)
		{
			wait1Msec(100);
			if (nMotorEncoder[encoderPort] == nLastControlEncoder)
			  break;

		  nLastControlEncoder = nMotorEncoder[encoderPort];
		}
		PlaySound(soundBlip);//Debugging

		nStartTime   = -1;

		motor[controlMotor]  = nPowerLevel;

		time1[T1] = 0;
		while (true)
		{
			if (nMotorEncoder[encoderPort] != nLastControlEncoder)
			{
			  nStartTime = time1[T1];
			  break;
			}
		}

		// Wait to allow to spin up to speed

		wait1Msec(500);

    nMotorEncoder[controlMotor] = 0;

	  nLastControlEncoder   = nMotorEncoder[encoderPort];
		time1[T1] = 0;

		motor[controlMotor]   = - nPowerLevel;

		while (true)
		{
			if (nMotorEncoder[encoderPort] < nLastControlEncoder)
			{
				nFlipTime = time1[T1];
				break;
			}
			nLastControlEncoder   = nMotorEncoder[encoderPort];
		}

		wait1Msec(500);

		nBrakeTime   = -1;
	  nLastControlEncoder   = nMotorEncoder[encoderPort];
		motor[controlMotor]   = 0;
		time1[T1] = 0;

		int nNumbOfNoMoves = 0;
		for (int i = 0; i < 700; ++i)
		{
			if (nMotorEncoder[encoderPort] != nLastControlEncoder)
			{
			  nBrakeTime = time1[T1];
			  nNumbOfNoMoves = 0;
			}
			else
			{
			  ++nNumbOfNoMoves;
			  if (nNumbOfNoMoves > 100)
			    break;
			}

			nLastControlEncoder   = nMotorEncoder[encoderPort];
			wait1Msec(1);
		}

		if (nStartTime < nStartTimeMin)
		  nStartTimeMin = nStartTime;
		if (nStartTime > nStartTimeMax)
		  nStartTimeMax = nStartTime;
		nStartTimeSum     += nStartTime;

		if (nFlipTime < nFlipTimeMin)
		  nFlipTimeMin = nFlipTime;
		if (nFlipTime > nFlipTimeMax)
		  nFlipTimeMax = nFlipTime;
    nFlipTimeSum      += nFlipTime;

		if (nBrakeTime < nBrakeTimeMin)
		  nBrakeTimeMin = nBrakeTime;
		if (nBrakeTime > nBrakeTimeMax)
		  nBrakeTimeMax = nBrakeTime;
    nBrakeTimeSum      += nBrakeTime;

		nStartTimeAvg     = nStartTimeSum   / nCycles;
		nFlipTimeAvg      = nFlipTimeSum    / nCycles;
		nBrakeTimeAvg     = nBrakeTimeSum   / nCycles;

		nxtDisplayTextLine(0, "# Cycles:  %3d", nCycles);

		string sTemp;
		string sNumbers;
    nxtDisplayCenteredTextLine(1, ".....Min Avg Max");

		StringFormat(sTemp, "Strt:%3d %3d", nStartTimeMin, nStartTimeAvg);
		StringFormat(sNumbers, "%s %3d", sTemp, nStartTimeMax);
		nxtDisplayTextLine(2, sNumbers);

		StringFormat(sTemp, "Flip:%3d %3d", nFlipTimeMin, nFlipTimeAvg);
		StringFormat(sNumbers, "%s %3d", sTemp, nFlipTimeMax);
		nxtDisplayTextLine(3, sNumbers);

		StringFormat(sTemp, "Brke:%3d %3d", nBrakeTimeMin, nBrakeTimeAvg);
		StringFormat(sNumbers, "%s %3d", sTemp, nBrakeTimeMax);
		nxtDisplayTextLine(4, sNumbers);
	}
}