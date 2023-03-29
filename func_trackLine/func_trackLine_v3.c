int detectSurface(long &red, long &green, long &blue)
{
	// Target values[][0 to 2] and tolerances[][3 to 5]
	const long TAPE [5][6] = {{80, 10, 8, 20, 5, 5}, // red tape
								{9, 9, 6, 5, 5, 5}, // black tape
								{38, 10, 8, 25, 5, 5}, // center
								{83, 91, 73, 15, 15, 15}, // white
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

void trackLine()
{
	// Alan
	SensorMode[S3] = modeEV3Color_Color;
	long red = 0, green = 0, blue = 0;
	drive(30, 30);
	while (detectSurface(red, green, blue) != 3)
	{}
	displayBigTextLine(1, "Line detected");
	int surface = detectSurface(red, green, blue);
	while (surface != 5)
	{
		surface = detectSurface(red, green, blue);
		if (surface == 1)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(10, 0);
		}
		else if (surface == 2)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(0, 10);
		}
		else if (surface == 3)
		{
			drive(20, 20);
		}
		else if (surface == 5)
		{
			drive(0, 0);
			displayBigTextLine(1, "Green");
		}
	}
}
