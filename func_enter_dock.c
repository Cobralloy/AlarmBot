void enter_dock(int motor_power)
{
  	drive(motor_power, -motor_power);
	while(getGyroDegrees(S2) != 0)
  	{}
  	drive(0, 0);
  	wait1Msec(1000);
  	drive(motor_power/2, motor_power/2);
  	while(readMuxSensor(msensor_S4_1) == 0)
  	{}
  	driveDistance(-3, -motor_power/2);
}
