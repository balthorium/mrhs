///////////////////////////////////////////////////////////////////////////////////////////
//
//                       Query FTC User Control Program
//
// The file "FTCConfig.txt" contains the name of the program that should be executed
// during the user control (tele-op) phase of a FTC competition. This is a short little
// program to read this file and display on the NXT LCD screen.
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma platform(NXT)     // This program only works on NXT -- generate error for other platforms

const string kConfigName = "FTCConfig.txt";

TFileIOResult nIoResult;
TFileHandle hFileHandle;

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

void getUserControlProgram(string& sFileName)
{
  byte   nParmToReadByte[2];
  int    nFileSize;

  sFileName = "";
  nParmToReadByte[1] = 0;
	hFileHandle = 0;
  OpenRead(hFileHandle, nIoResult, kConfigName, nFileSize);
  if (nIoResult == ioRsltSuccess)
  {
    for (int index = 0; index < nFileSize; ++index)
	  {
	    ReadByte(hFileHandle, nIoResult,  nParmToReadByte[0]);
	  	strcat(sFileName, &nParmToReadByte[0]);
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

///////////////////////////////////////////////////////////////////////////////////////////
//
//                                        main
//
// Main task simply displays the name of the FTC program on the NXT LCD.
//
///////////////////////////////////////////////////////////////////////////////////////////
task main()
{
  string sFileName;

  getUserControlProgram(sFileName);
  nxtDisplayTextLine(1, "User Program:");
  nxtDisplayTextLine(2, sFileName);

  while (true)
  {}
}
