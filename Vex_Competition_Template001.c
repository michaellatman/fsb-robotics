#pragma config(Motor,  port2,           LeftFront,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           LeftRear,      tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RightFront,    tmotorVex393, openLoop)
#pragma config(Motor,  port5,           RightRear,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
int threshold = 35; //Global threshold

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{

		//We're using Maacanum Wheels
		//Thank too https://github.com/andyzhang1994/ for channels
		int y1 = vexRT[Ch3];// Left y axis is y1 forward backwards
    int x1 = vexRT[Ch4];// Left x axis is x1 strafe left right
    int x2 = vexRT[Ch1];// Right x axis is y2 rotation
    int y2 = vexRT[Ch2];// angle control

    if(y1<threshold) y1=0;
    if(y2<threshold) y2=0;
    if(x1<threshold) x1=0;
    if(x2<threshold) x2=0;


    int LF = 0; //Left-front
    int RF = 0; //Right-front
    int LR = 0; //Left-rear
    int RR = 0; //Right-rear

    // Handle Strafing Movement
    LF+= y1;
    LF -= y1;
    LR -= y1;
    LR += y1;

    //Handle Regular Movement

    LF += x1;
    RF += x1;
    LR += x1;
    RR += x1;

    //Handle Turning Movement

    LF += x1;
    RF += x1;
    LR -= x1;
    RR -= x1;

    // Apply Finished values to motors.

    motor[RightFront] =  RF;
    motor[RightRear] =  RR;
    motor[LeftFront] =  LF;
    motor[LeftRear] =  LR;










	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}
