int angle_generator ()
{
	srand(nSysTime);
	int random_angle = abs(rand() % 360+1);
	return random_angle;
}


void rotate_robot(int angle)
{
	resetGyro(S2);
	if(angle <180)
	{
		motor[motorA] = 50;
		motor[motorD] = -motor[motorA];
		while (getGyroDegrees(S2)<angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}
	else
	{
		resetGyro(S2);
		angle = 360.0 - angle;
		motor[motorA] = -50;
		motor[motorD] = -motor[motorA];
		while (abs(getGyroDegrees(S2))<angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}
}

void configure_sensors ()
{
	SensorType [S4] = sensorEV3_Ultrasonic;
	SensorType [S2] = sensorEV3_Gyro;
	wait1Msec (300);
	SensorMode [S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec (300);
	SensorMode [S2] = modeEV3Gyro_Calibration;
	wait1Msec(300);
	SensorType[S3] = sensorSoundDBA;
	wait1Msec(300);
	SensorType[S1] = sensorEV3_Color;
	wait1Msec(300);
	SensorMode[S1] = modeEV3Color_Color;
}

task main()
{
	displayString(5,"Please push a button to start");
	while (!getButtonPress(buttonAny))
	{}
	configure_sensors();
	float angle = 0;
	
	while (SensorValue(S1) < 20) /* Threshold value of 20 dB was used as the value rarely crossed the 75 dB mark and mostly stayed around the 
		30-50dB mark*/
	{}
	
	while (SensorValue(S1) > 20)
	{
		angle = angle_generator();
		rotate_robot(angle);
		motor[motorA] = motor[motorD] = -100;
		while (SensorValue(S4)> 60 || SensorValue(S1) != (int)colorRed) // Touch sensor will be added to code once we get the expandable port
		{}
	}
}
