
void configureSensors();
void drive(int left, int right);

void trackLine()
{
	// Alan
	//const int THRESHOLD = 50;
	//const int TOLERANCE = 10;
	drive(20,20);
	while (SensorValue[S3] != (int) colorRed && SensorValue[S3] != (int) colorBlack)
	{}
	displayBigTextLine(1, "Line detected");
	while (SensorValue[S3] != (int) colorGreen)
	{
		if (SensorValue[S3] == (int) colorBlack)
		{
			displayBigTextLine(1, "Black detected");
			drive(0,20);
		}
		else if (SensorValue[S3] == (int) colorRed)
		{
			displayBigTextLine(1, "Red detected");
			drive(20,0);
		}
	}
	displayBigTextLine(1, "Green detected");
	drive(0,0);
}

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
