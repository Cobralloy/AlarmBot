task main()
{
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(100);
	long red = 0, green = 0, blue = 0;
	while (true)
	{
		long colour = detectSurface(red, green, blue);
		if (colour == 1)
			displayBigTextLine(2, "Red");
		else if (colour == 2)
			displayBigTextLine(2, "Black");
		else if (colour == 3)
			displayBigTextLine(2, "Center");
		else if (colour == 4)
			displayBigTextLine(2, "White");
		else if (colour == 5)
			displayBigTextLine(2, "Green");
		else if (colour == 0)
			displayBigTextLine(2, "Unknown");
		displayBigTextLine(4, "%d %d %d", red, green, blue);
	}
}
