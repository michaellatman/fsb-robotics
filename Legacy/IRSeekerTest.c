#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     liftheight,     sensorI2CHiTechnicColor)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     HTIRS3,         sensorI2CCustom)
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
#define max( a, b ) ( ((a) &gt; (b)) ? (a) : (b) )
#endif

#include "C:\Program Files\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
// global variables
long nNumbCyles;
long nInits = 0;
string sTextLines[8];


// function prototypes
void displayText(int nLineNumber, const string cChar, int nValueDC, int nValueAC);
void displayInstructions();

// main task
task main ()
{
    int stage = 1;
    int _dirDC = 0;
    int _dirAC = 0;
    int lacS1, lacS2, lacS3, lacS4, lacS5 = 0;
    int acS1, acS2, acS3, acS4, acS5 = 0;

    // the default DSP mode is 1200 Hz.
    tHTIRS2DSPMode _mode = DSP_1200;

    // show the user what to do
    displayInstructions();
    while(true)
    {
        // You can switch between the two different DSP modes by pressing the
        // orange enter button

        PlaySound(soundBeepBeep);
        while(bSoundActive)
        {}
        eraseDisplay();
        nNumbCyles = 0;
        ++nInits;
        while (true)
        {
            if ((nNumbCyles & 0x04) == 0)
            nxtDisplayTextLine(0, "Initializing...");
            else
            nxtDisplayTextLine(0, "");
            nxtDisplayCenteredBigTextLine(1, "IR Seekr");

            // set the DSP to the new mode
            if (HTIRS2setDSPMode(HTIRS2, _mode))
            break; // Sensor initialized

            ++nNumbCyles;
            //PlaySound(soundShortBlip);
            nxtDisplayTextLine(4, "Inits: %d / %d", nInits, nNumbCyles);
            nxtDisplayCenteredTextLine(6, "Connect Sensor");
            nxtDisplayCenteredTextLine(7, "to Port S2");
            wait1Msec(100);
        }

        eraseDisplay();
        nxtDisplayTextLine(0, "      Left  Right");

        waitForStart();
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
            if (!HTIRS2readAllACStrength(HTIRS3, lacS1, lacS2, lacS3, lacS4, lacS5 ))
            break; // I2C read error occurred

            displayText(1, "D", _dirDC, _dirAC);
            displayText(2, "1", lacS1, acS1);
            displayText(3, "2", lacS2, acS2);
            displayText(4, "3", lacS3, acS3);
            displayText(5, "4", lacS4, acS4);
            displayText(6, "5", lacS5, acS5);
            displayText(7, "Stage", stage, 0);
        }
    }
}

// Display the instructions to the user
void displayInstructions()
{
    nxtDisplayCenteredTextLine(0, "Autonomous");
    nxtDisplayCenteredBigTextLine(1, "By Michael");
    nxtDisplayCenteredTextLine(2, "& Ryan");
    wait1Msec(2000);
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
