void stopDriveMotors(){
	motor[driveL] = 0;
  motor[driveFL] = 0;
  motor[driveR] = 0;
  motor[driveFR] = 0;
}

void checkAndYell(){
	if(externalBattery<8000){
		PlayImmediateTone(277, 5000);
	}
}

void YMOVE(int speed){
		motor[driveL] = speed;
    motor[driveFL] = speed;
    motor[driveR] = speed;
    motor[driveFR] = speed;
}

void YMOVE(int speed, float duration){
	YMOVE(speed);
	wait1Msec(duration);
	stopDriveMotors();
}

void XMOVE(int speed){
		motor[driveL] = speed;
    motor[driveFL] = speed;
    motor[driveR] = -speed;
    motor[driveFR] = -speed;
}

void XMOVE(int speed, float duration){
	XMOVE(speed);
	wait1Msec(duration);
	stopDriveMotors();
}

void ROTATE(int speed){
	motor[driveL] = -speed;
  motor[driveFL] = speed;
  motor[driveR] = speed;
  motor[driveFR] = -speed;
}

void ROTATE(int speed, float duration){
	ROTATE(speed);
	wait1Msec(duration);
	stopDriveMotors();
}
