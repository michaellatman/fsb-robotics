#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     liftheight,     sensorI2CHiTechnicColor)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     arm2,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     driveL,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    binlift,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    linesensor,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "AdvancedSensors.c"
task main()
{
	waitForStart();
	servo[binlift] = 129;
	int runs = 0;
	const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"

  SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor
				int nRed;
    		int nGreen;
    		int nBlue;
	getRGB(kColorSensorPort, nRed, nGreen, nBlue);
	while(nGreen>nBlue&&nRed>nBlue||nBlue>120){
          		getRGB(kColorSensorPort, nRed, nGreen, nBlue);
			    		motor[arm] = motor[arm2] = 100;
			    		runs++;
			  			nxtDisplayTextLine(2, "Color:  %d",  (short) SensorValue[kColorSensorPort]);
			  			nxtDisplayTextLine(3, "Red:    %d",  nRed);
			  			nxtDisplayTextLine(4, "Green:  %d",  nGreen);
			  			nxtDisplayTextLine(5, "Blue:   %d",  nBlue);
			  			//wait1Msec(500);
			    		//motor[arm2] = -100;
	}
	motor[arm] = motor[arm2] = 0;
	wait1Msec(0);

	while(SensorValue(sonarSensor) > 28){
          				//We may have reached the rack although the number above is varible and I have to do more research.

      motor[driveL] = motor[driveR] = 100;

  }
  wait1Msec(500);
  while(SensorValue(sonarSensor) > 28){
          				//We may have reached the rack although the number above is varible and I have to do more research.

      motor[driveL] = motor[driveR] = 100;

  }
  motor[driveL] = motor[driveR] = 0;



	wait1Msec(1000);
  runs = 0;
  	getRGB(kColorSensorPort, nRed, nGreen, nBlue);
	while(nRed < nGreen&&nRed<nBlue||nGreen > 100||nRed == 255&&runs<30){
          		getRGB(kColorSensorPort, nRed, nGreen, nBlue);
			    		motor[arm] = motor[arm2] = -100;
			    		runs++;
			    		//motor[arm2] = -100;
	}
	motor[arm] = motor[arm2] = 0;

	motor[driveL] = motor[driveR] = -100;
	wait1Msec(3000);
	motor[driveL] = motor[driveR] = 0;
	servo[binlift] = 255;
	servo[binlift] = 0;


}
