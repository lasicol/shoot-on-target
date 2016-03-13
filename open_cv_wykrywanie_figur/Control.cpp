#include "Control.h"



Control::Control(Point targetCenterr, Point laserPositionn)
{
	laserPosition = laserPositionn;
	targetCenter = targetCenterr;
}


Control::~Control()
{
}

void Control::countControlValue()
{
	int e_x = targetCenter.x - laserPosition.x;
	int e_y = targetCenter.y - laserPosition.y;

	if (e_x == 0 && e_y > 0) // jest wyzej od celu
	{
		lastDirection = (DirectionEnum)DOWN;
	//	return (DirectionEnum)DOWN;
	}
	else if (e_x == 0 && e_y < 0) // jest nizej od celu
	{
		lastDirection = (DirectionEnum)UP;
	//	return (DirectionEnum)UP;
	}
	else if (e_x < 0 && e_y == 0) // jest po prawej stronie celu
	{
		lastDirection = (DirectionEnum)LEFT;
	//	return (DirectionEnum)LEFT;
	}
	else if (e_x > 0 && e_y == 0) // jest po lewej stronie celu
	{
		lastDirection = (DirectionEnum)RIGHT;
	//	return (DirectionEnum)RIGHT;
	}

	else if (e_x > 0 && e_y > 0) // jest up-left
	{
		lastDirection = (DirectionEnum)DOWN_RIGHT;
	//	return (DirectionEnum)DOWN_RIGHT;
	}
	else if (e_x > 0 && e_y < 0) // jest down-left
	{
		lastDirection = (DirectionEnum)UP_RIGHT;
	//	return (DirectionEnum)UP_RIGHT;
	}
	else if (e_x < 0 && e_y > 0) // jest up-right
	{
		lastDirection = (DirectionEnum)DOWN_LEFT;
	//	return (DirectionEnum)DOWN_LEFT;
	}
	else if (e_x > 0 && e_y > 0) // jest down-right
	{
		lastDirection = (DirectionEnum)UP_LEFT;
	//	return (DirectionEnum)UP_LEFT;
	}
}
