bool alarmStatus (bool driving, bool &lastStatus)
{
	// Alan
	const int DB_THRESHOLD = 30;
	const int DURATION_THRESHOLD = 1000;
	if (driving)
	{
		if (SensorValue[S1] < DB_THRESHOLD)
		{
			if (!lastStatus)
			{
				if (time1[T1] > DURATION_THRESHOLD)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				lastStatus = false;
				time1[T1] = 0;
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (SensorValue[S1] > DB_THRESHOLD)
		{
			if (lastStatus)
			{
				if (time1[T1] > DURATION_THRESHOLD)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				lastStatus = true;
				time1[T1] = 0;
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}
