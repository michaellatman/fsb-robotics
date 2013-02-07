#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveR2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     driveL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     driveL2,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    binlift,              tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)

//#pragma config(Servo,  srvo_S1_C3_6,    release,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  mtr_S1_C4_1,    Collecter,            tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

task main(){
	//1const int THRESHOLD = 5;
	getJoystickSettings (joystick);

	//bool turbo = false;
	waitForStart();   // wait for start of tele-op phase
	//servo[armRelease] = 0;
	int tick = 0;
	int bin = 255;
	//servo[binlift] = 30;
	while(true)
	{
		tick++;
		/*if (joy1Btn(7)) {
			turbo = !turbo;
		}*/
      	/*motor[DFR] =  ((joystick.joy1_y1) - (joystick.joy1_x1) - (joystick.joy1_x2));
       	motor[DFL] = (-(joystick.joy1_y1) - (joystick.joy1_x1) - (joystick.joy1_x2))/2;
       	motor[DBR] = ((joystick.joy1_y1) + (joystick.joy1_x1) - (joystick.joy1_x2))/2;
       	motor[DBL] =  (-(joystick.joy1_y1) + (joystick.joy1_x1) - (joystick.joy1_x2))/2;/**/

       	float onex = joystick.joy1_x1;
       	float oney = joystick.joy1_y1;
       	float twox = joystick.joy1_x2;
       	float twoy = joystick.joy1_y2;




       	if(abs(onex)<6)onex=0;

       	if(abs(oney)<6)oney=0;


       	if(abs(twox)<16)twox=0;

       	if(abs(twoy)<16)twoy=0;

       	int left;
       	int right;

       	left = oney/3;
       	right = oney/3;

       	left+= twox/3;
       	right-=twox/3;

       	if (joy1Btn(3))
         {
          	left = -100;
          	right = -100;

          }

       	motor[driveL] = left;
       	motor[driveL2] = left;

       	motor[driveR] = right;
       	motor[driveR2] = right;




					int speed = 0;

					if (joy1Btn(1))
          {
          	//int escape = 0;
          	//servo[binlift2] = 139;
          	servo[binlift] = 120;
          	bin = 120;
          	//motor[arm] = -50;
          	//wait1Msec(200);
          	//motor[arm]= 0;
          }
          if (joy1Btn(2))
          {
          	servo[binlift] = 161;
          	bin = 161;

          }



          if (joy1Btn(8))
          {
              speed = -100;
          }
          else if (joy1Btn(6))
          {
              speed = 100;
          }
          motor[arm] = speed;

          //servo[binlift] = 0;
          if(tick > 20){
	          if (joy1Btn(5))
	          {

	          	bin++;

	          }
	          else if (joy1Btn(7))
	          {
	          	bin--;
	          }
	          if(bin>200) bin = 200;
	          if(bin<30) bin = 30;
	          tick=0;
        	}
        	nxtDisplayTextLine(0,"This is one %d",bin);
          servo[binlift] = bin;
          //servo[binlift2] = bin;
  	}
}
