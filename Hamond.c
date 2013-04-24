#pragma config(Sensor, S1,     Test,           sensorHiTechnicTouchMux)
#pragma config(Motor,  motorA,          Left,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          Right,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Proximity,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AdvancedSensors.c"

task main ()
{
	int nButtonsMask;
	SensorType[S4] = sensorHiTechnicTouchMux;
	while(true){


//
// The sensor value is a 4-bit map indicating which of the possible four
// touch sensors are pressed.
//
	nButtonsMask = SensorValue[S4];
		if(nButtonsMask & 0x08){
  		motor[Left] = 0;
  		motor[Right] = 0;
  	}
  	else{
  		motor[Left] = 50;
  		motor[Right] = 50;
  	}
	}



}

/*
* $Id: hitechnic-irseeker-v2-test1.c 109 2012-09-25 17:10:26Z xander $
*/
