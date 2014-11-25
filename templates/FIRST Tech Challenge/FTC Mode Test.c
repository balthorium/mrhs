#include "JoystickDriver.c"

task main()
{
  while(true) //continously loop to check for "mode" switching
  {
    getJoystickSettings(joystick); //update joystick values from FMS
    //if (joystick.UserMode == false) //While in "autonomous" mode (UserMode = false)
    if (0 == joystick.UserMode) //While in "autonomous" mode (UserMode = false)
    //if (false == (short) joystick.UserMode) //While in "autonomous" mode (UserMode = false)
    //if (!joystick.UserMode) //While in "autonomous" mode (UserMode = false)
    {
      //do autonomous
      if( joystick.StopPgm == true )
      {
        // we are disabled
        nxtDisplayClearTextLine( 4 );
        nxtDisplayTextLine( 4, "Disabled Autonomous" );
      }
      else
      {
        // we are enabled
        nxtDisplayClearTextLine( 4 );
        nxtDisplayTextLine( 4, "Running Autonomous" );
      }
    }
    else //While in "User Control" mode (UserMode = false)
    {
      //do usercontrol
      if( joystick.StopPgm == true )
      {
        // we are disabled
        nxtDisplayClearTextLine( 4 );
        nxtDisplayTextLine( 4, "Disabled Teleop" );
      }
      else
      {
        // we are enabled
        nxtDisplayClearTextLine( 4 );
        nxtDisplayTextLine( 4, "Running Teleop" );
      }
    }

    // wait for next packet
    wait1Msec( 50 );
  }
}
