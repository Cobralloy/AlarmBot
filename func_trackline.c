int detectSurface(long &red, long &green, long &blue)
{
	// Target values[][0 to 2] and tolerances[][3 to 5]
	const long TAPE [5][6] = {{80, 10, 8, 20, 5, 5}, // red tape
				{8, 9, 6, 5, 5, 5}, // black tape
				{40, 16, 8, 30, 12, 5}, // center
				{74, 82, 67, 20, 20, 20}, // white
				{32, 57, 10, 25, 10, 15}}; // green
	getColorRGB(S3, red, green, blue);
	for (int i = 0; i <= 4; i++)
	{
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
	long red = 0, green = 0, blue = 0;
	
	// Drive forward until line is detected
	drive(30, 30);
	while (detectSurface(red, green, blue) != 3)
	{}
	
	int surface = detectSurface(red, green, blue);
	while (surface != 5)
	{
		surface = detectSurface(red, green, blue);
		if (surface == 1)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(15, 3);
			drive(0, 3); // Correct overshoot
			wait1Msec(30);
		}
		else if (surface == 2)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(3, 15);
			drive(3, 0);
			wait1Msec(30);
		}
		else if (surface == 3)
		{
			drive(30, 30);
		}
		else if (surface == 5)
		{
			drive(0, 0);
			displayBigTextLine(1, "Green");
		}
	}
}
