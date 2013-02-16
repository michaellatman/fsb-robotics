#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     liftheight,     sensorI2CHiTechnicColor)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveL,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    binlift,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    linesensor,           tServoStandard)
#include "AdvancedSensors.c"

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
	//
	waitForStart();   // wait for start of tele-op phase
	//servo[armRelease] = 0;
	int tick = 0;
	int bin = 99;
	//servo[binlift] = 30;
	const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"

  SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor
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

				int nRed;
    		int nGreen;
    		int nBlue;

			  getRGB(kColorSensorPort, nRed, nGreen, nBlue);
			  nxtDisplayTextLine(2, "Color:  %d",  (short) SensorValue[kColorSensorPort]);
			  nxtDisplayTextLine(3, "Red:    %d",  nRed);
			  nxtDisplayTextLine(4, "Green:  %d",  nGreen);
			  nxtDisplayTextLine(5, "Blue:   %d",  nBlue);


       	if(abs(onex)<6)onex=0;

       	if(abs(oney)<6)oney=0;


       	if(abs(twox)<16)twox=0;

       	if(abs(twoy)<16)twoy=0;

       	int left;
       	int right;

       	float divide;
       	divide = 2;
       	if (joy1Btn(2))
        {
        	divide = .1;
        }
       	left = oney/divide;
       	right = oney/divide;

       	left+= twox/(divide);
       	right-=twox/(divide);

       	motor[driveL] = left;

       	motor[driveR] = right;





					int speed = 0;

					if (joy1Btn(1))
          {
          	//int escape = 0;
          	//servo[binlift2] = 139;


          	while(nRed < nGreen&&nRed<nBlue||nGreen > 155||nRed == 255){
          		getRGB(kColorSensorPort, nRed, nGreen, nBlue);
			    		motor[arm] = -100;
			  		}
			  		motor[arm] = 0;
			  		servo[binlift] = 99;
          	bin = 99;


          	//motor[arm] = -50;
          	//wait1Msec(200);
          	//motor[arm]= 0;
          }
          if (joy1Btn(3))
          {
          	/*
          	servo[binlift] = 139;
          	bin = 139;
          	motor[arm] = -80;
          	motor[DFL] = 50;
          	motor[DFR] = -50;
          	motor[DBL] = 50;
          	motor[DBR] = -50;
          	wait1Msec(200);
          	motor[arm]= 0;
          	wait10Msec(100);
          	motor[DFL] = 0;
          	motor[DFR] = 0;
          	motor[DBL] = 0;
          	motor[DBR] = 0;
          	*/

          }


          if (joy1Btn(8))
          {
              speed = -100;
          }
          else if (joy1Btn(6))
          {
              speed = 100;
          }



			    if((nRed > nGreen&&nRed>nBlue)&&speed<0&&nGreen!=255){
			    	speed = 0;
			  	}
			  	else if((nGreen > nRed&&nGreen>nBlue)&&speed>0&&nBlue!=255){
			    	speed = 0;
			  	}

          motor[arm] = speed;

          //servo[binlift] = 0;
          if(tick > 7){
	          if (joy1Btn(5))
	          {

	          	bin--;

	          }
	          else if (joy1Btn(7))
	          {
	          	bin++;
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
