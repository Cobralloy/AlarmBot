#include "UW_sensorMux.c"

void configureSensors();
void drive(int left, int right);
void driveDistance (int cm, int power);
void rotateAngle(int angle, int power);
int randomAngle(int lower, int upper);

task main()
{
	displayBigTextLine(1, "DBA: %d", SensorValue[S4]); // Sound sensor
	displayBigTextLine(4,"C1 %d",readMuxSensor(msensor_S1_1)); // Touch sensor
	displayBigTextLine(8,"C2 %d",readMuxSensor(msensor_S1_2)); // Ultrasonic Sensor
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
	SensorType[S1] = sensorEV3_GenericI2C;
	wait1Msec(100);
	initSensorMux(msensor_S1_1, touchStateBump);
	initSensorMux(msensor_S1_2, sonarCM);
}

void drive(int left, int right)
{
	motor[motorA] = -left;
	motor[motorD] = -right;
}

void driveDistance (int cm, int power)
{
	cm *= -1;
	const float CM_TO_DEG = 180/(2.75*PI);
	int initialCount = nMotorEncoder[motorA];
	int targetCount = initialCount + cm*CM_TO_DEG;
	if (initialCount < targetCount)
	{
		motor[motorA] = motor[motorD] = power;
		while (nMotorEncoder[motorA] < targetCount)
		{}
	}
	else
	{
		motor[motorA] = motor[motorD] = -power;
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

void rotateAngle(int angle, int power) // rotates robot in place to given angle then stops. Positive angles are clockwise when viewed from above
{
	int initialAngle = getGyroDegrees(S2);
	int targetAngle = initialAngle + angle;
	if (angle > 0)
	{
		drive(power, -power);
		while(getGyroDegrees(S2) < targetAngle)
		{}
	}
	else
	{
		drive(-power, power);
		while(getGyroDegrees(S2) > targetAngle)
		{}
	}
	wait1Msec(50);
	if (getGyroDegrees(S2) < targetAngle) // robot needs to rotate clockwise to correct error
	{
		drive(10,-10);
		while(getGyroDegrees(S2) < targetAngle)
		{}
	}
	else if (getGyroDegrees(S2) > targetAngle) // robot needs to rotate counterclockwise to correct error
	{
		drive(-10,10);
		while(getGyroDegrees(S2) > targetAngle)
		{}
	}
	drive(0, 0);
}

int randomAngle(int lower, int upper)
{
	srand(nSysTime);
	int range = upper - lower;
	return (rand() % range + lower);
}
