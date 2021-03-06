
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     touch,          sensorTouch)
#pragma config(Sensor, S3,     colorSensor,    sensorCOLORFULL)
#pragma config(Sensor, S4,     sideTouch,      sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     Shoulder,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Spin,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     driveFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     driveFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     driveR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     driveL,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AdvancedSensors.c"


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
/*
 * This task handles driving.
 * It's job is to compute the values for each motor to ensure proper movement regardless on direction..
 */
task drive(){
	while(true){
		//Get controller values
	 	float x1 = joystick.joy1_x1;
	 	float y1 = joystick.joy1_y1;
	 	float x2 = joystick.joy1_x2;
	 	float y2 = joystick.joy1_y2;
	 	//If the controller is less than 12 let's count it as zero.
	 	if(abs(x1)<12)x1=0;
	 	if(abs(y1)<12)y1=0;
	 	if(abs(x2)<12)x2=0;
	 	if(abs(y2)<12)y2=0;
	 	//Scale down the controller to keep controllers in drivers hands
		x1*=.787;
		x2*=.787;
		y1*=.787;
		y2*=.787;
	  int LF = 0; //Left-front
	  int RF = 0; //Right-front
	  int LR = 0; //Left-rear
	  int RR = 0; //Right-rear

	  // Handle StrafiRightFrontng Movement
	  LF += x1;
	  RF -= x1;
	  LR += x1;
	  RR -= x1;
	  //Handle Regular Movement
	  LF += y1;
	  RF += y1;
	  LR += y1;
	  RR += y1;
	  //Handle Turning Movement
	  LF += x2;
	  RF -= x2;
	  LR -= x2;
	  RR += x2;
		// Apply Finished values to motors.
	 	motor[driveL] = LR;
	 	motor[driveFL] = LF;
	 	motor[driveR] = RR;
	 	motor[driveFR] = RF;
	 	wait1Msec(05);
	}
}
bool sto;
int lastShoulder = 100; // The last shoulder position.. In this case we are setting to 100 for testing.
int shoulderRate = 0; //The current movement rate of the arm. Should be zero at this point.

/*
 * This task handles mainting shoulder position.
 * It's job is to keep track of the encoder on the arm, along with the encoder changes to calculate speed.
 */
task shoulderControl(){
	while(true){
		lastShoulder = nMotorEncoder[Shoulder]; //We're at this position
		while(true){
			shoulderRate = nMotorEncoder[Shoulder]-lastShoulder; //Current-last = rate


			if(joy1Btn(06)&&nMotorEncoder[Shoulder]<1300){
						if(shoulderRate<20){
							motor[Shoulder] = 80;
						}
						else{
							motor[Shoulder] = 40;
						}
						sto = true;
			}

			else if(joy1Btn(08)){
						sto = true;
						if(shoulderRate>-1){
							motor[Shoulder] = -20;
						}
						else if(shoulderRate<-5){
							motor[Shoulder] = 25;
						}
			}
			else if(sto){

				if(nMotorEncoder[Shoulder]>957) motor[Shoulder] = 15;
				else motor[Shoulder] = 20;

				sto=false;
			}
			else{
				motor[Shoulder] = 15;
			}
			lastShoulder = nMotorEncoder[Shoulder];
			wait1Msec(10);
		}

		wait1Msec(100);
	}
}
task liftControl(){
	while(true){

	if(joystick.joy1_TopHat==0){
		//wristLoc = 124;
		//stopTask(shoulderControl);
		motor[Lift]=80;
	}
	else if(joystick.joy1_TopHat==4){
		//wristLoc = 124;
		//StartTask(shoulderControl);
		motor[Lift]=-80;
	}
	else{
		motor[Lift]=0;
	}
	wait1Msec(10);
	abortTimeslice();
	}
}

bool spinning = false;
task handControl(){
	while(true){
		if(spinning){
			if(joy1Btn(01)){
					motor[Spin] = -100;
			}
			else{
					motor[Spin] = 100;
			}
		}
		else if(!joy1Btn(01)) motor[Spin] = 0;
		else motor[Spin] = -100;
		if(joy1Btn(09)){
			while(joy1Btn(09)){
				wait1Msec(10);
			}
			spinning = !spinning;
		}
		wait1Msec(10);
	}
}
task main(){
	nMotorEncoder[Shoulder]=0;
	//1const int THRESHOLD = 5;
	getJoystickSettings (joystick);

	//bool turbo = false;
	//


	//servo[Bro] = 5000;
	waitForStart();   // wait for start of tele-op phase
	//servo[armRelease] = 0;

	//servo[binlift] = 30;
	//const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"


  //SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor

  //Initial Setup


  /*
 		Setup arm at correct angles
  */

	//servo[hand] = 50;

  StartTask(drive,10);
  //StartTask(wristControl);
  StartTask(handControl);
  StartTask(shoulderControl);
  StartTask(liftControl);
	while(true)
	{

		wait1Msec(100);
  }
}
