task main()
{
	configureSensors();
	int readings[NUM_READINGS];
	int timestamps[NUM_READINGS];
	for (int i = 0; i < NUM_READINGS; i++)
	{
		readings[i] = 0;
		timestamps[i] = 0;
	}
	int index = 0;
	while(true)
	{
		bool alarmOn = false;
		alarmOn = alarmStatus(readings, timestamps, index);
		if (alarmOn)
		{
			motor[motorB] = 50;
		}
		else
		{
			motor[motorB] = 0;
		}
		displayBigTextLine(3, "%d %d %d", alarmOn, calculateMean(readings), returnMax(readings));
		displayBigTextLine(5, "DB: %d", SensorValue[S4]);
	}
}
