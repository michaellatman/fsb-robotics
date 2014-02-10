
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
void test(int speed, int m){
	motor[m] = speed;
	wait1Msec(200);
	motor[m] = -speed;
	wait1Msec(200);
	motor[m] = 0;
	wait1Msec(1000);
}
void testSlow(int speed, int m){
	motor[m] = speed;
	wait1Msec(200);
	motor[m] = -speed;
	wait1Msec(200);
	motor[m] = 1;
	wait1Msec(1000);
}
task main()
{
	test(100,Spin);
	test(100,DriveFR);
	test(100,DriveFL);
	test(100,DriveR);
	test(100,DriveL);
	test(100,Lift);
	testSlow(30,Shoulder);


}
