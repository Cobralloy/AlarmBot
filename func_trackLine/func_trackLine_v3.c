int detectSurface(long &red, long &green, long &blue)
{
	// Target values[][0 to 2] and tolerances[][3 to 5]
	const long TAPE [4][6] = {{78, 10, 8, 5, 5, 5}, // red tape
								{6, 9, 6, 5, 5, 5}, // black tape
								{50, 15, 15, 10, 5, 5}, // center
								{83, 91, 73, 10, 10, 10}}; // white
	// WEEF Lab RGB values: {r, g, b}
	getColorRGB(S3, red, green, blue);
	for (int i = 0; i <= 3; i++)
	{
		if (abs(TAPE[i][0] - red) < TAPE[i][3] 
			&& abs(TAPE[i][1] - green) < TAPE[i][4] 
			&& abs(TAPE[i][2] - blue) < TAPE[i][5])
		{
			return i+1; // red tape 1, black tape 2, center 3, white 4
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
	while (detectSurface(red, green, blue) != 4)
	{
		if (surface == 1)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(20, 0);
		}
		else if (surface == 2)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(0, 20);
		}
		else if (surface == 3)
		{
			drive(30,30);
		}	
		else
		{
			drive(0, 0);
		}
	}
	
}

