
void configureSensors();
void drive(int left, int right);

task main()
{
	configureSensors();
	trackLine();
}

void configureSensors()
{
	SensorType[S1] = sensorSoundDBA;
	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
}

void drive(int left, int right)
{
	motor[motorA] = -left;
	motor[motorD] = -right;
}
