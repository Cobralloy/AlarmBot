const int NUM_READINGS = 40; // MS_INTERVAL * NUM_READINGS = READING WINDOW

float calculateMean(ubyte *values)
{
	float sum = 0;
	for (int i = 0; i < NUM_READINGS; i++)
		sum += values[i];
	return sum / NUM_READINGS;
}

int returnMax(ubyte *values)
{
	int max = 0;
	for (int i = 0; i < NUM_READINGS; i++)
		if (values[i] > max)
			max = values[i];
	return max;
}

bool alarmStatus(ubyte *readings, int *timestamps, int &index)
{
	const float THRESHOLD = 20;
	const int MS_INTERVAL = 50; // MS_INTERVAL * NUM_READINGS = READING WINDOW
	if (index == 0)
	{
		if (time1[T1] - timestamps[NUM_READINGS-1] > MS_INTERVAL)
		{
			timestamps[index] = time1[T1];
			readings[index] = SensorValue[S4];
			index++;
		}
	}
	else
	{
		if (time1[T1] - timestamps[index-1] > MS_INTERVAL)
		{
			timestamps[index] = time1[T1];
			readings[index] = SensorValue[S4];
			index++;
		}

	}
	if (index > NUM_READINGS)
		index = 0;
	if (calculateMean(readings) > THRESHOLD && returnMax(readings) > 40)
		return true;
	return false;
}
