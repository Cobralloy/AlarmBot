void avoid_obstacles ()
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
	else if (readMuxSensor(msensor_S1_2) < LENGTH + 30)
	{
		rotateRandomAngle(30, 90, 50);
	}
}
