void avoid_obstacles ()
{
	// Avoid Obstacle Function - Prabhjyot Paul
	const float LENGTH = 30;
	while (readMuxSensor(msensor_S1_2) < LENGTH + 30 || readMuxSensor(msensor_S1_1) == 1 || SensorValue[S3] == (int) colorRed)
	{
		if (SensorValue[S3] == (int) colorRed)
		{
			rotateRandomAngle (90,180,50);
		}
		else if (readMuxSensor(msensor_S1_1) == 1)
		{
			drive(-15, 70);
			rotateRandomAngle(45, 90, 50);
		}
		else if (readMuxSensor(msensor_S1_2) < LENGTH)
		{
			rotateRandomAngle (120,180,100);
		}
		else
		{
			rotateRandomAngle(30, 90, 50);
		}
	}
}
