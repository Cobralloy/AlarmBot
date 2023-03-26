void avoid_obstacles ()
{
	while (SensorValue(sonarCM) < 35 || SensorValue(touchStateBump) == 1 || SensorValue(S3) == (int)colorRed)
	{
		if(SensorValue (S3) == (int)colorRed)
		{
			rotateRandomAngle (90,180,50 );
		}
		else if (SensorValue(sonarCM) < 35)
		{
			rotateRandomAngle (10,135,65 );
		}
		else
		{
			rotateRandomAngle (45,167,75)
		}
	}
}
