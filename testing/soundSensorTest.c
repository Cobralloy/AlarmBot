
task main()
{
	SensorType[S1] = sensorSoundDBA;
	while(!getButtonPress(buttonEnter))
	{
		int soundLevel = SensorValue[S1];
		displayBigTextLine(1, "DBA: %d", soundLevel);
	}
}
