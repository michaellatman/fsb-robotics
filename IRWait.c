#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     Sonar,          sensorSONAR)
#pragma config(Sensor, S4,     HTGYRO,         sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     Shoulder,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Spin,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     driveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     driveR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     driveL,        tmotorTetrix, openLoop)
#include "Shiela.h"
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-irseeker-v2-test2.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * hitechnic-irseeker-v2.h provides an API for the HiTechnic IR Seeker V2.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER.

 * Xander Soldaat (xander_at_botbench.com)
 * Dick Swan
 * Gus Jansson
 * 04 October 2012
 * version 0.1
 */

#include "drivers/hitechnic-irseeker-v2.h"


#include "drivers/hitechnic-gyro.h"
// function prototypes


int set = 1;
int sticky = 1000;
task driveToRamp(){
	nxtDisplayClearTextLine(2);
	nxtDisplayClearTextLine(3);
	int direction = 1;
	if(set==2)direction=-1;

	//Back up
	YMOVE(-30,400);

	//Move Right OR Left if the second set
  if(set==1)XMOVE(30,2000);
  if(set==2)XMOVE(50,2900);
  if(set==3)XMOVE(50,3400);

  //Foward
  YMOVE(100,100);

  //Move Right
	if(set==1)XMOVE(30,800);
  if(set==2||set==3)XMOVE(30,1000);


	//Foward
  YMOVE(100,1600);

	float rotSpeed = 0;
  float heading = 0;

  // Calibrate the gyro, make sure you hold the sensor still
  HTGYROstartCal(HTGYRO);

  // Reset the timer.
  time1[T1] = 0;

  while (abs(heading)<20)
  {
    // Wait until 20ms has passed
    while (time1[T1] < 20)
      wait1Msec(1);
		if(set==1)ROTATE(50);
		if(set==2||set==3)ROTATE(50);
	//	if(set==2)ROTATE(-50);
    // Reset the timer
    time1[T1]=0;

    // Read the current rotation speed
    rotSpeed = HTGYROreadRot(HTGYRO);

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    if(abs(rotSpeed)>0.05)
    heading += rotSpeed * 0.02;

    // Display our current heading on the screen
    //nxtDisplayCenteredBigTextLine(3, "%2.0f", heading);
  }

  //wait1Msec(500);


  motor[Shoulder]=-40;
  wait1Msec(300);
  motor[Shoulder]=15;

  YMOVE(-100,1900);
	StopTask(driveToRamp);
}
task moveDump(){
	while(true){
		YMOVE(50);
		SensorType[Sonar] = sensorSONAR;
		int nValue = SensorValue[Sonar];
		ClearTimer(T1);
		while((nValue>31||nValue==255)&&time1[T1]<5000){
			nValue = SensorValue[Sonar];
		}
		stopDriveMotors();
		wait1Msec(200);
		if(set!=1)XMOVE(40,200);
		wait1Msec(500);
		motor[Spin] = -100;
		wait1Msec(1000);
		motor[Spin] = 0;
		StartTask(driveToRamp);
		StopTask(moveDump);

	}
}
task shoulderSticky(){
	while(true){
		if(nMotorEncoder[Shoulder]<sticky){
			motor[Shoulder]=100;
		}
		else{
			motor[Shoulder]=15;
			wait1Msec(200);
			StartTask(moveDump);
			StopTask(shoulderSticky);
		}
		wait1Msec(100);
	}
}
	//int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;

task Seek(){
	ClearTimer(T1);
	time100[T1] = 0;
	while(true){
		HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );
	 	if(abs(acS5-acS4)<30&&acS5+acS4>70){
	 				if(time100[T1] > 20) set = 2;
					if(time100[T1] > 25) set = 3;
      			nxtDisplayClearTextLine(2);
      		nxtDisplayString(2,"Ahead");
      		wait1Msec(0);

      		 PlaySound(soundBeepBeep);

      		StartTask(shoulderSticky);
      		stopDriveMotors();
      		StopTask(Seek);
      	}
      	else{
      		nxtDisplayClearTextLine(2);
      		nxtDisplayString(2,"No");
					XMOVE(-40);
      	}
     }
}
#include "JoystickDriver.c"
task main ()
{


	checkAndYell();
  // show the user what to do
  //waitForStart();

	//wait10Msec(1000);
	YMOVE(100,500);
	XMOVE(100,1000);
	wait10Msec(10);
  StartTask(Seek);
  while(true)
  {
  	wait1Msec(10);
	}
}
