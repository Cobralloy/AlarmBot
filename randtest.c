task main()
{
	srand(nSysTime);
	for (int i = 0; i < 4; i++)
	{
		int num = abs(rand() % 10) + 1;
		displayBigTextLine(i*2, "Number: %d", num);
	}

	while(!getButtonPress(buttonEnter))
	{}
}
