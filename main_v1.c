#include "UW_sensorMux.c"
#include "trivial_functions.c"
#include "func_alarmStatus_v4.c"
#include "func_rotateRandomAngle.c"
#include "func_avoid_obstacles.c"
#include "func_disconnectCharger_v1.c"
#include "func_enter_dock_v3.c"
#include "func_trackLine_v3.c"

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
	while (alarmStatus(readings, timestamps, index))
	{
		avoid_obstacles();
		drive(100, 100);
	}
	trackLine();
	enter_dock();
}
