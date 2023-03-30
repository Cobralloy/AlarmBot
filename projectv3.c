void configureSensors();
void drive(int left, int right);
void driveDistance (int cm, int motorPower);
void rotateAngle(int angle, int motorPower);
int randomAngle(int lower, int upper);

const int LENGTH = 30;

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

void avoid_obstacles ()
{
	long red = 0, green = 0, blue = 0;
	if (detectSurface(red, green, blue) == 1)
	{
		rotateAngle(randomAngle(90, 110), 30);
		wait1Msec(500);
		if (detectSurface(red, green, blue) != 4)
		rotateAngle(180, 50);
	}
	else if (SensorValue[S1] < LENGTH)
	{
		rotateAngle(randomAngle(140, 180), 80);
		wait1Msec(200);
	}
	else if (SensorValue[S1] < LENGTH + 20)
	{
		rotateAngle(randomAngle(60, 120), 30);
		wait1Msec(500);
	}
}

const int NUM_READINGS = 40; // MS_INTERVAL * NUM_READINGS = READING WINDOW

float calculateMean(ubyte *values)
{
	float sum = 0;
	for (int i = 0; i < NUM_READINGS; i++)
		sum += values[i];
	return sum / NUM_READINGS;
}

int returnMax(ubyte *values)
{
	ubyte max = 0;
	for (int i = 0; i < NUM_READINGS; i++)
		if (values[i] > max)
			max = values[i];
	return max;
}

bool alarmStatus(ubyte *readings, int *timestamps, int &index)
{
	const float THRESHOLD = 20;
	const int MS_INTERVAL = 50; // MS_INTERVAL * NUM_READINGS = READING WINDOW
	if (index == 0 ? time1[T1] - timestamps[NUM_READINGS-1] > MS_INTERVAL : time1[T1] - timestamps[index-1] > MS_INTERVAL)
	{
		timestamps[index] = time1[T1];
		readings[index] = SensorValue[S4];
		index++;
	}
	if (index > NUM_READINGS)
		index = 0;
	if (calculateMean(readings) > THRESHOLD && returnMax(readings) > 40)
		return true;
	return false;
}

void enter_dock()
{
	const int motor_power = 10;
	if (getGyroDegrees(S2) % 360 > 180)
		drive(motor_power, -motor_power);
	else if (getGyroDegrees(S2) % 360 < 180)
		drive(-motor_power, motor_power);
	while(getGyroDegrees(S2) % 360 != 0)
	{}
	drive(0, 0);
	wait1Msec(1000);
	driveDistance(10, motor_power/2);
}

bool disconnectCharger() //Devaditya Chakrabarty
{
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 100;
	wait1Msec(500);
	drive(-100,-100);
	clearTimer(T2);
	while(nMotorEncoder[motorB] < 90 && time1[T2] < 3000)
	{}
	drive(0,0);
	motor[motorB] = 0;
	if (time1[T2] > 2999)
	{
		driveDistance(2, 100);
		return false;
	}
	else
	{
		return true;
	}
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
				drive(15, 3);
			drive(0, 3);
			wait1Msec(50);
		}
		else if (surface == 2)
		{
			while (detectSurface(red, green, blue) != 3)
				drive(3, 15);
			drive(3, 0);
			wait1Msec(50);
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

task main()
{
	configureSensors();

	// Initialization for alarmStatus
	ubyte readings[NUM_READINGS];
	int timestamps[NUM_READINGS];
	for (int i = 0; i < NUM_READINGS; i++)
	{
		readings[i] = 0;
		timestamps[i] = 0;
	}
	int index = 0;

	while (!alarmStatus(readings, timestamps, index))
	{}
	bool disconnected = disconnectCharger();
	if (!disconnected)
		return;
	driveDistance(-30, 100);
	rotateAngle(180, 100);
	//while (alarmStatus(readings, timestamps, index))
	driveDistance(50, 30);
	while (!getButtonPress(buttonAny))
	{
		avoid_obstacles();
		drive(40, 40);
	}
	trackLine();
	enter_dock();
}

void configureSensors()
{
	SensorType[S4] = sensorSoundDBA;
	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S1] = sensorEV3_Ultrasonic;
}

void drive(int left, int right)
{
	motor[motorA] = -left;
	motor[motorD] = -right;
}

void driveDistance (int cm, int motorPower)
{
	cm *= -1;
	const float CM_TO_DEG = 180/(2.75*PI);
	int initialCount = nMotorEncoder[motorA];
	int targetCount = initialCount + cm*CM_TO_DEG;
	if (initialCount < targetCount)
	{
		motor[motorA] = motor[motorD] = motorPower;
		while (nMotorEncoder[motorA] < targetCount)
		{}
	}
	else
	{
		motor[motorA] = motor[motorD] = -motorPower;
		while (nMotorEncoder[motorA] > targetCount)
		{}
	}
	wait1Msec(50);
	if (nMotorEncoder[motorA] < targetCount)
	{
		motor[motorA] = motor[motorD] = 10;
		while (nMotorEncoder[motorA] < targetCount)
		{}
	}
	else if (nMotorEncoder[motorA] > targetCount)
	{
		motor[motorA] = motor[motorD] = -10;
		while (nMotorEncoder[motorA] > targetCount)
		{}
	}
	motor[motorA] = motor[motorD] = 0;
}

void rotateAngle(int angle, int motorPower) // rotates robot in place to given angle then stops. Positive angles are clockwise when viewed from above
{
	int initialAngle = getGyroDegrees(S2);
	int targetAngle = initialAngle + angle;
	if (angle > 0)
	{
		drive(motorPower, -motorPower);
		while(getGyroDegrees(S2) < targetAngle)
		{}
	}
	else
	{
		drive(-motorPower, motorPower);
		while(getGyroDegrees(S2) > targetAngle)
		{}
	}
	wait1Msec(50);
	if (getGyroDegrees(S2) < targetAngle) // robot needs to rotate clockwise to correct error
	{
		drive(20,-20);
		while(getGyroDegrees(S2) < targetAngle)
		{}
	}
	else if (getGyroDegrees(S2) > targetAngle) // robot needs to rotate counterclockwise to correct error
	{
		drive(-20,20);
		while(getGyroDegrees(S2) > targetAngle)
		{}
	}
	drive(0, 0);
}

int randomAngle(int lower, int upper)
{
	srand(nSysTime);
	long n =0;
	do
	{
		 n = randLong() % 3 - 1;
	} while (n == 0);
	return (randLong() % (upper-lower) + lower)*n;
}
