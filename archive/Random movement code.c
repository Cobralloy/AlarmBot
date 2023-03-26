int coordinate_generator ()
{
	srand(nSysTime);
	int random_coor = abs(rand() % 11);
	return random_coor - 5;
}

float rotation_angle (int x_coor, int y_coor, int d_x, int d_y)
{
	float numerator = ((x_coor * d_x) + (y_coor * d_y));
	float denominator = (sqrt (pow(x_coor,2) + pow(y_coor,2)))*(sqrt (pow(d_x,2) + pow(d_y,2)));
	return radiansToDegrees((acos(numerator/denominator)));
}

void rotate_robot(float angle)
{
	resetGyro(S2);
	if(angle <180)
	{
		motor[motorA] = 50;
		motor[motorD] = -motor[motorA];
		while (getGyroDegrees(S2)<angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}
	else
	{
		resetGyro(S2);
		angle = 360.0 - angle;
		motor[motorA] = -50;
		motor[motorD] = -motor[motorA];
		while (abs(getGyroDegrees(S2))<angle)
		{}
		motor[motorA] = motor[motorD] = 0;
	}
}

void configure_sensors ()
{
	SensorType [S4] = sensorEV3_Ultrasonic;
	SensorType [S2] = sensorEV3_Gyro;
	wait1Msec (300);
	SensorMode [S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec (300);
	SensorMode [S2] = modeEV3Gyro_Calibration;
	wait1Msec(300);
}

task main()
{
	displayString(5,"Please push a button to start");
	while (!getButtonPress(buttonAny))
	{}
	configure_sensors();
	int initial_x = 1, initial_y = 0;
	int delta_x = 0;
	int delta_y = 0;
	float angle = 0;
	for (int count = 0; count < 100; count++)
	{
		while (SensorValue(S4) <= 60)
		{
		delta_x = coordinate_generator();
		delta_y = coordinate_generator()-3;
		angle = rotation_angle(initial_x, initial_y, delta_x, delta_y);
		rotate_robot(angle);
		motor[motorA] = motor[motorD] = -100;
		initial_x = delta_x;
		initial_y = delta_y;
		wait1Msec(1000);
		}
		delta_x = coordinate_generator();
		delta_y = coordinate_generator()-3;
		angle = rotation_angle(initial_x, initial_y, delta_x, delta_y);
		rotate_robot(angle);
		motor[motorA] = motor[motorD] = -100;
		initial_x = delta_x;
		initial_y = delta_y;
		wait1Msec(3000);
	}


}
