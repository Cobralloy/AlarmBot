void rotateRandomAngle (int min_angle, int max_angle, int motorpower)
{
	int angle = randomAngle (-180,180);
	while (abs(angle) < min_angle && abs(angle) > max_angle)
		angle = randomAngle (-180,180);
	rotate(angle,motorpower);
}
