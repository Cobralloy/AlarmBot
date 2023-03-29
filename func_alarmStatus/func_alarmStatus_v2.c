bool alarmStatus (bool &driving, bool &lastStatus)
{
	// Alan
	const int DB_THRESHOLD = 30;
	const int DURATION_THRESHOLD = 1000;
	if (driving)
	{
		if (SensorValue[S4] < DB_THRESHOLD)
		{
			if (!lastStatus && time1[T1] > DURATION_THRESHOLD)
			{
				driving = false;
			}
			else
			{
				lastStatus = false;
				time1[T1] = 0;
			}
		}
	}
	else
	{
		if (SensorValue[S4] > DB_THRESHOLD)
		{
			if (lastStatus && time1[T1] > DURATION_THRESHOLD)
			{
				driving = true;
			}
			else
			{
				lastStatus = true;
				time1[T1] = 0;
			}
		}
	}
	return driving;
}
