int detectSurface(long &red, long &green, long &blue)
{
	// Target values[][0 to 2] and tolerances[][3 to 5]
	const long TAPE [5][6] = {{85, 10, 8, 20, 5, 5}, // red tape
								{9, 9, 6, 5, 5, 5}, // black tape
								{41, 15, 8, 25, 10, 5}, // center
								{78, 86, 70, 20, 20, 20}, // white
								{32, 57, 10, 25, 10, 15}}; // green
	// WEEF Lab RGB values: {r, g, b}
	getColorRGB(S3, red, green, blue);
	for (int i = 0; i <= 4; i++)
	{
		//displayBigTextLine(6, "%d %d %d", abs(TAPE[4][0] - red), abs(TAPE[4][1] - green), abs(TAPE[i][2] - blue) < TAPE[4][5]);
		//displayBigTextLine(8, "%d %d %d", TAPE[4][3], TAPE[4][4], TAPE[4][5]);
		if (abs(TAPE[i][0] - red) < TAPE[i][3]		// compare red
			&& abs(TAPE[i][1] - green) < TAPE[i][4] // compare green
			&& abs(TAPE[i][2] - blue) < TAPE[i][5]) // compare blue
		{
			return i+1; // red tape 1, black tape 2, center 3, white 4, green 5
		}
	}
	return 0; // none 0
}

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
