void enter_dock()
{
	const int motor_power = 30;
	if (getGyroDegrees(S2) > 180)
		drive(motor_power, -motor_power);
	else if (getGyroDegrees(S2) < 180)
		drive(-motor_power, motor_power);
	while(getGyroDegrees(S2) % 360 != 0)
	{}
	drive(0, 0);
	wait1Msec(1000);
	drive(motor_power/2, motor_power/2);
	while(readMuxSensor(msensor_S1_1) == 0)
	{}
	driveDistance(-5, -motor_power/2);
}
