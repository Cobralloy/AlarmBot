void trackLine()
{
	// Alan
	drive(20,20);
	while (SensorValue[S3] != (int) colorRed && SensorValue[S3] != (int) colorBlack)
	{}
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
