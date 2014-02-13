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

	float Er;
	float El;
void moveInches(float x, float y){
	float tim1, float tim2, float rot1l, float rot2l, float rot1r, float rot2r;
	float vel = 17;
	nMotorEncoder[driveR] = 0;
	nMotorEncoder[driveL] = 0;
	 Er = -nMotorEncoder[driveR]/1440.0*PI*4;
	 El = -nMotorEncoder[driveL]/1440.0*PI*4;
	float angle = atan2(y, x);
	while((abs(Er)<=abs(y-x)+10)&&(abs(El)<=abs(y+x)+10)){
		tim1 = time1[T1];
		rot1r = -nMotorEncoder[driveR];
		rot1l = -nMotorEncoder[driveL];
		wait1Msec(20);
		Er = -nMotorEncoder[driveR]/1440.0*PI*4;
		El = -nMotorEncoder[driveL]/1440.0*PI*4;
		motor[driveFR] = motor[driveL] = sin(angle)*vel-cos(angle)*vel;
		motor[driveFL] = motor[driveR] = sin(angle)*vel+cos(angle)*vel;
	}
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
}=--
