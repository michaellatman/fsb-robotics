#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     driveA,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(NXT, TETRIX)
#include "AdvancedSensors.c"
#include "JoystickDriver.c"
task main(){
	waitForStart();
	const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"
	getJoystickSettings (joystick);
  SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor
  float one = 0;
	float two = 0;
	float lift = 0;
	float value = 1;
	while(true)
		{
				wait1Msec(5);

				float onex = joystick.joy1_x1;
       	float oney = joystick.joy1_y1;
       	float twox = joystick.joy1_x2;
       	float twoy = joystick.joy1_y2;
				lift += oney/250;
				if(lift<0) lift = 0;
				if(lift>255) lift = 255;
       	if ((onex > 16)||(onex < -16))
       		value += onex/250;
				nxtDisplayTextLine(1, "One:  %d\n Two: %d",one,two);
       	nxtDisplayTextLine(2, "Value: %d",value);
       	//one = one + onex;
       	//two = two + twox;

       	if(value > 255) value = 255;
				if(value < 0) value = 0;

				one = (value/2)-10+lift;
				two = value;

       	if(one > 255) one = 255;
				if(one < 0) one = 0;
				if(two > 255) two = 255;
				if(two < 0) two = 0;

       	servo[servo2] = -one;// - one;
       	servo[servo3] = one;// + one;

       	servo[servo4] = -two;
       	servo[servo5] = two;


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