#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     SL,            tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     SR,            tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     DFL,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     DFR,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     DBL,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     DBR,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     Collect,       tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an Tetrix robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  motor[DFR] = 100;
  motor[DFL]= 100;
}


///////////ing is the main code for the autonomous robot operation. Customize as appropriate for
// your specif//////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The followic robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"

void drive_foward(int time, int speed){
    motor[DFR] = speed;
    motor[DFL]= -speed;
    motor[DBR] = speed;
    motor[DBL]= -speed;
    wait1Msec(time);
    motor[DFR] = 0;
    motor[DFL]= 0;
    motor[DBR] = 0;
    motor[DBL]= 0;
}
void turn_right(int degrees){
    int time = degrees*(50/9);
    int speed = 100;
    motor[DFR] = -speed;
    motor[DFL]= -speed;
    motor[DBR] = -speed;
    motor[DBL]= -speed;
    wait1Msec(time);
    motor[DFR] = 0;
    motor[DFL]= 0;
    motor[DBR] = 0;
    motor[DBL]= 0;
}
task main()
{
  waitForStart();
  drive_foward(3900,150);
  //wait10Msec(20);


  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////


}
