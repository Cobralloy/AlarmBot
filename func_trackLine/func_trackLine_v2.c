void trackLine()
{
	// Alan
	SensorMode[S3] = modeEV3Color_Ambient;
	const int THRESHOLD = 50, TOLERANCE = 10, WHITE = 70;
	const int FAST = 30, MEDIUM = 20, SLOW = 10;
	drive(20,20);
	while (abs(SensorValue[S3] - THRESHOLD) < TOLERANCE)
	{}
	displayBigTextLine(1, "Line detected");
	while (SensorValue[S3] < WHITE)
	{
		if (abs(SensorValue[S3] - THRESHOLD) < TOLERANCE)
		{
			displayBigTextLine(1, "Center detected");
			drive(MEDIUM, MEDIUM);
		}
		else if (SensorValue[S3] < THRESHOLD)
		{
			displayBigTextLine(1, "Black detected");
			drive(SLOW, FAST);
		}
		else if (SensorValue[S3] > THRESHOLD)
		{
			displayBigTextLine(1, "Red detected");
			drive(FAST, SLOW);
		}
	}
	displayBigTextLine(1, "White detected");
	drive(0,0);
}
