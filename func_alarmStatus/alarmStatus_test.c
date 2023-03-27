task main()
{
	bool lastStatus = false;
	bool driving = false;
	while(true)
	{
		driving = alarmStatus(driving, lastStatus);
		if (driving)
		{
			motor[motorB] = 50;
		}
		else
		{
			motor[motorB] = 0;
		}
		displayBigTextLine(3, "%d", driving);
		displayBigTextLine(5, "DB: %d", SensorValue[S1]);
	}
}
