bool disconnectCharger() //Devaditya Chakrabarty
{
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 100;
	wait1Msec(1000);
	drive(-100,-100);
	clearTimer(T2);
	while(nMotorEncoder[motorB] < 90 && time1[T2] < 3000)
	{}
	drive(0,0);
	motor[motorB] = 0;
	if(time1[T2] > 2999)
	{
		driveDistance(10, 100)
		return false;
	}
	else
	{
		return true;
	}
}
