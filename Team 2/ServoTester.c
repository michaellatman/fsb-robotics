#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     driveA,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,      ,             tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(NXT, TETRIX)
#include "AdvancedSensors.c"
#include "JoystickDriver.c"
task main(){
	float lol = 0;
	while(0!=1){
		lol = 255;
		servo[servo1] = lol;
	  servo[servo2] = lol;
	  servo[servo3] = 0;
	  servo[servo4] = 0;
	  servo[servo5] = lol;
	  servo[servo6] = lol;
	  nxtDisplayTextLine(0,"This is one %d",lol);
	  wait1Msec(500);
	  lol = 0;
	  nxtDisplayTextLine(0,"This is one %d",lol);
		servo[servo1] = lol;
	  servo[servo2] = lol;
	  servo[servo3] = 0;
	  servo[servo4] = 0;
	  servo[servo5] = lol;
	  servo[servo6] = lol;
	  wait1Msec(500);
	}
	/*servo[servo3] = 130;
	servo[servo2] = 125;
  servo[servo1] = 200;
  servo[servo4] = 125;
  servo[servo5] = 125;
	wait1Msec(5000);
	//servo[servo3] = 35;
	//servo[servo2] = 220;
	wait1Msec(1000);*/



	/*motor[driveA] = 100;
	wait1Msec(4000);
	int nRed;
  int nGreen;
  int nBlue;
	while(nRed < (nRed+nGreen+nBlue/3)*2&&nRed<100){
		getRGB(kColorSensorPort, nRed, nGreen, nBlue);
		motor[driveA] = -50;
		nxtDisplayTextLine(2, "Color:  %d",  (short) SensorValue[kColorSensorPort]);
    nxtDisplayTextLine(3, "Red:    %d",  nRed);
    nxtDisplayTextLine(4, "Green:  %d",  nGreen);
    nxtDisplayTextLine(5, "Blue:   %d",  nBlue);
	}
	motor[driveA] = -100;*/
}
