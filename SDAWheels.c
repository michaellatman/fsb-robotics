#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     liftheight,     sensorI2CHiTechnicColor)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     sonarSensor,         sensorSONAR)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "AdvancedSensors.c"
// global variables
//long nNumbCyles;
//long nInits = 0;
string sTextLines[8];

//int GoBackFor = 500; //Reverse time
//int SpinFor = 500; //Turn time

// function prototypes
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC);
void displayInstructions();

string dir = "right";
int nRed;
int nGreen;
int nBlue;
// main task
task main ()
{
//    int last = 0;
    int flags = 0;
    int stage = 1;
    int _dirDC = 0;
    int _dirAC = 0;
    //int lacS1, lacS2, lacS3, lacS4, lacS5 = 0;
    int acS1, acS2, acS3, acS4, acS5 = 0;


    // the default DSP mode is 1200 Hz.
//    tHTIRS2DSPMode _mode = DSP_1200;

    // show the user what to do
    displayInstructions();
    while(true)
    {
        // You can switch between the two different DSP modes by pressing the
        // orange enter button

        PlaySound(soundBeepBeep);
        eraseDisplay();
        nxtDisplayTextLine(0, "      AC");
				const tSensors kColorSensorPort   = S2;	// We want the color sensor to be on port "S2"

  			SensorType[kColorSensorPort] = sensorI2CHiTechnicColor; // Configure the sensor
        getRGB(kColorSensorPort, nRed, nGreen, nBlue);
        waitForStart();
        servo[binlift] = 121;
        while (true)
        {
            // Read the current non modulated signal direction
            _dirDC = HTIRS2readDCDir(HTIRS2);

            // read the current modulated signal direction
            _dirAC = HTIRS2readACDir(HTIRS2);

            // Read the individual signal strengths of the internal sensors
            // Do this for both unmodulated (DC) and modulated signals (AC)

            if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
            break; // I2C read error occurred
            //if (!HTIRS2readAllACStrength(HTIRS3, lacS1, lacS2, lacS3, lacS4, lacS5 ))
            //break; // I2C read error occurred

            //Displays all sensor fields. We will condense this when we do final research.
            eraseDisplay();
            nxtDisplayTextLine(2, "1:  %d", acS1);
            nxtDisplayTextLine(3, "2:  %d", acS2);
            nxtDisplayTextLine(4, "3:  %d", acS3);
            nxtDisplayTextLine(5, "4:  %d", acS4);
            nxtDisplayTextLine(6, "5:  %d", acS5,);
            nxtDisplayTextLine(7, "Stage: %d", stage);

            int sensor = acS3;

            if(stage == 1){
            	//Drive foward
            	getRGB(kColorSensorPort, nRed, nGreen, nBlue);
            	while((nGreen < nRed&&nGreen<nBlue)||nGreen<40||nGreen == 255){
			    			motor[arm] = 100;
			    			getRGB(kColorSensorPort, nRed, nGreen, nBlue);
			  			}


			  			motor[arm] = 0;
			    		motor[driveL] = motor[driveR] = 50;

            	if(acS2+sensor+acS4 > 30){

			  					motor[arm] = 0;
            			//We see it, stop and go to stage 2. Also set flags to zero, we'll need those later.
            			motor[driveL] = motor[driveR] = 0;
            			stage ++;
            			writeDebugStreamLine("Stage!");
            			flags = 0;

            	}
          	}
          	else if(stage == 2){
          			//Set motors in proper directions
									if(acS3>(acS4+acS2+80)){
	          				motor[driveL] = 50;
	          				motor[driveR] = 50;
	          			}
	          			else if(acS2+acS1 > acS4+acS5){
	          				motor[driveL] = 0;
	          				motor[driveR] = 50;
	          			}
	          			else if(acS4+acS5 > acS2+acS1){
	          				motor[driveL] = 50;
	          				motor[driveR] = 0;
	          			}

          			//If the value fell add a flag. If not set to zero.

          			if(SensorValue(sonarSensor) < 25){
          				//We may have reached the rack although the number above is varible and I have to do more research.
          				motor[driveL] = motor[driveR] = 0;
          				stage++;
          			}
          	}
          	else if(stage == 3){
          		motor[arm] = -50;
          		wait1Msec(1000);
          		motor[arm] = 0;
          		motor[driveL] = motor[driveR] = -50;
          		wait1Msec(2000);
          		motor[driveL] = motor[driveR] = 0;
          		stage ++;
          	}
        }
    }
}

// Display the instructions to the user
void displayInstructions()
{
    nxtDisplayCenteredTextLine(0, "Autonomous");
    nxtDisplayCenteredBigTextLine(3, "By Michael");
    nxtDisplayCenteredTextLine(5, "& Ryan");
    //As much as I like my own name let's only keep this up for a few moments
    wait1Msec(500);
}

// Minimize LCD screen flicker by only updating LCD when data has changed
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC)
{
    string sTemp;

    StringFormat(sTemp, "%4d  %4d", nValueDC, nValueAC);
    // Check if the new line is the same as the previous one
    // Only update screen if it's different.
    if (sTemp != sTextLines[nLineNumber])
    {
        string sTemp2;

        sTextLines[nLineNumber] = sTemp;
        StringFormat(sTemp2, "%s:  %s", cChar, sTemp);
        nxtDisplayTextLine(nLineNumber, sTemp2);
    }
}

/*
* $Id: hitechnic-irseeker-v2-test1.c 109 2012-09-25 17:10:26Z xander $
*/
