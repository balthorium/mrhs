///////////////////////////////////////////////////////////////////////////////////////////
//
//                                        displayDiagnostics
//
// THis program will display diagnostic information about a FTC robot on the NXT LCD.
//
// If you want to use the LCD for your own debugging use, call the function
// "disableDiagnosticsDisplay()
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma systemFile            // this eliminates warning for "unreferenced" functions
#pragma autoStartTasks

bool bDisplayDiagnostics = true;  // Set to false in user program to disable diagnostic display

void getUserControlProgram(string& sFileName);

void disableDiagnosticsDisplay()
{
  bDisplayDiagnostics = false;   // Disable diagnostic display
}


task displayDiagnostics()
{
  string sFileName;

  getUserControlProgram(sFileName);
	nxtDisplayTextLine(6, "Teleop FileName:");
	nxtDisplayTextLine(7, sFileName);
  bNxtLCDStatusDisplay = true;
  while (true)
	{
		if (bDisplayDiagnostics)
		{
			getJoystickSettings(joystick);                   //Update variables with current joystick values

			if (joystick.StopPgm)
			  nxtDisplayCenteredTextLine(1, "Wait for Start");
			else if (joystick.UserMode)
				nxtDisplayCenteredTextLine(1, "TeleOp Running");
			else
				nxtDisplayCenteredTextLine(1, "Auton Running");

			if ( externalBatteryAvg < 0)
				nxtDisplayTextLine(3, "Ext Batt: OFF");       //External battery is off or not connected
			else
				nxtDisplayTextLine(3, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);

			nxtDisplayTextLine(4, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);   // Display NXT Battery Voltage

			nxtDisplayTextLine(5, "FMS Msgs: %d", nMessageCount);   // Display Count of FMS messages
		}

		wait1Msec(200);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//                                        getUserControlProgram
//
// This function returns the name of the FTC User Control program. It reads the file
// "FTCConfig.txt" and builds the name of the file from the contents.
//
// Note that the filename includes the ".rxe" (robot executable file) file extension.
//
///////////////////////////////////////////////////////////////////////////////////////////

const string kConfigName = "FTCConfig.txt";

void getUserControlProgram(string& sFileName)
{
  byte   nParmToReadByte[2];
  int    nFileSize;
	TFileIOResult nIoResult;
	TFileHandle hFileHandle;

  sFileName = "";
  nParmToReadByte[1] = 0;
  hFileHandle = 0;
  OpenRead(hFileHandle, nIoResult, kConfigName, nFileSize);
  if (nIoResult == ioRsltSuccess)
  {
    for (int index = 0; index < nFileSize; ++index)
    {
      ReadByte(hFileHandle, nIoResult,  nParmToReadByte[0]);
      strcat(sFileName, nParmToReadByte);
    }

    //
    // Delete the ".rxe" file extension
    //
    int nFileExtPosition;

    nFileExtPosition = strlen(sFileName) - 4;
    if (nFileExtPosition > 0)
      StringDelete(sFileName, nFileExtPosition, 4);
  }
  Close(hFileHandle, nIoResult);
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    waitForStart
//
// Wait for the start of either the autonomous or tele-op phase. User program is running on the NXT
// but the phase has not yet started. The FMS (Field Management System) is continually (every 50 msec)
// sending information to the NXT. This program loops getting the latest value of joystick settings.
// When it finds that the FMS has started the  phase, it immediately returns.
//
// Perhaps this function should be moved into the "JoystickDriver.c" file.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void waitForStart()
{
  while (true)
  {
    getJoystickSettings(joystick);
    if (!joystick.StopPgm)
      break;
  }
  return;
}
