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
	float tim1, tim2, rot1l, rot2l, rot1r, rot2r;
	float Mr, Ml;
	float vel = 17;
	float Vri, Vli;
	float Vr, Vl;
	nMotorEncoder[driveR] = 0;
	nMotorEncoder[driveL] = 0;
	 Er = -nMotorEncoder[driveR]/1440.0*PI*4;
	 El = -nMotorEncoder[driveL]/1440.0*PI*4;
	float angle = atan2(y, x);
	//motor[driveFR] = motor[driveL] = sin(angle)*vel-cos(angle)*vel;
	//motor[driveFL] = motor[driveR] = sin(angle)*vel+cos(angle)*vel;
	Vri = sin(angle)*vel+cos(angle)*vel;
	Vli = sin(angle)*vel-cos(angle)*vel;
	while((abs(Er)<=abs(y-x))&&(abs(El)<=abs(y+x))){
		Ml = motor[driveFR] = motor[driveL] = sin(angle)*vel-cos(angle)*vel;
		Mr = motor[driveFL] = motor[driveR] = sin(angle)*vel+cos(angle)*vel;
		tim1 = time1[T1];
		rot1r = -nMotorEncoder[driveR];
		rot1l = -nMotorEncoder[driveL];
		wait1Msec(20);
		tim2 = time1[T1];
		rot2r = -nMotorEncoder[driveR];
		rot2l = -nMotorEncoder[driveL];
		Vr = (rot2r-rot1r)/(tim2-tim1)/1440*4*PI;
		Vl = (rot2l-rot1l)/(tim2-tim1)/1440*4*PI;
		//Er = -nMotorEncoder[driveR]/1440.0*PI*4;
		//El = -nMotorEncoder[driveL]/1440.0*PI*4;
		if (Vri > 0 && Vri > Vr) motor[driveFL] = motor[driveR] = Mr = Mr+5;
		if (Vli > 0 && Vli > Vl) motor[driveFR] = motor[driveL] = Ml = Ml+5;
		if (Vri < 0 && Vri < Vr) motor[driveFL] = motor[driveR] = Mr = Mr-5;
		if (Vli < 0 && Vli < Vl) motor[driveFR] = motor[driveL] = Ml = Ml-5;
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
}
