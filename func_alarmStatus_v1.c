bool alarmStatus (bool driving, bool &lastStatus)
{
	// Alan
	if (driving)
	{
		if (SensorValue[S1] < 75)
		{
			if (!lastStatus)
			{
				if (time1[T1] > 3000)
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
		if (SensorValue[S1] > 75)
		{
			if (lastStatus)
			{
				if (time1[T1] > 3000)
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
