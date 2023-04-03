#include "UW_SensorMux.c"

// Function prototypes for trivial functions
void configureSensors();
void drive(int left, int right);
void driveDistance (int cm, int motorPower);
void rotateAngle(int angle, int motorPower);
int randomAngle(int lower, int upper);

const int LENGTH = 30; // Length of robot
#include "func_trackline.c" 
/* Line tracking function included separately so when RGB values and tolerances are changed, 
they can automatically be applied to the main program as well as any 
other programs used to test functions
*/

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
	else if (SensorValue[S1] < LENGTH) // Rotate more quickly and further if the user's hand is above the phone
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

const int NUM_READINGS = 40; 

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

bool alarmStatus(ubyte *readings, int &timestamp, int &index) // ubyte used to avoid exceeding memory limit
{
	const float THRESHOLD = 25;
	const float MAX_THRESHOLD = 70;
	const int MS_INTERVAL = 50; // MS_INTERVAL * NUM_READINGS = reading window for rolling average
	
	if (time1[T1] - timestamp > MS_INTERVAL) 
	{
		timestamp = time1[T1];
		readings[index] = SensorValue[S4];
		index++;
	}
	if (index > NUM_READINGS)
		index = 0;
	// return true if average and peak volume threshold are both met
	if (calculateMean(readings) > THRESHOLD && returnMax(readings) > MAX_THRESHOLD) 
		return true;
	return false;
}

void enter_dock()
{
	const int motor_power = 20;
	rotateAngle(90, 30);
	wait1Msec(1000);
	driveDistance(35, motor_power);
}

bool disconnectCharger() 
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
		driveDistance(2, 100); // Relieve charging cables of tension if disconnecting fails
		return false;
	}
	else
	{
		return true;
	}
}


task main()
{
	configureSensors();

	// Initialization for alarmStatus
	ubyte readings[NUM_READINGS];
	int timestamp = 0;
	for (int i = 0; i < NUM_READINGS; i++)
	{
		readings[i] = 0;
	}
	int index = 0;
	
	// Wait for alarm
	while (!alarmStatus(readings, timestamp, index))
	{}
	
	// Disconnect chargers and enter preset area
	bool disconnected = disconnectCharger();
	if (!disconnected)
		return;
	driveDistance(-40, 100);
	rotateAngle(180, 100);
	driveDistance(50, 30);
	
	// Avoid obstacles and user while waiting for alarm to turn off
	while (alarmStatus(readings, timestamp, index))
	{
		avoid_obstacles();
		drive(80, 80);
	}
	
	// Return to dock
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
