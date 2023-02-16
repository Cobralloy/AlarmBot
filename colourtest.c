
task main()
{
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	while(!getButtonPress(buttonEnter))
	{
		int colour = SensorValue[S3];
		displayBigTextLine(2, "Colour: %d", colour);
	}
}
