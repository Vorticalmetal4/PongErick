#include "CollisionSystem.h"

#include <cmath>

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::Square_Square(Position* Object1Pos, Position* Object2Pos, Dimension* Object1Dim, Dimension* Object2Dim)
{
	if ((Object1Pos->x + Object1Dim->Width > Object2Pos->x) && (Object1Pos->x < Object2Pos->x + Object2Dim->Width) && (Object1Pos->y + Object1Dim->Height > Object2Pos->y) && (Object1Pos->y < Object2Pos->y + Object2Dim->Height))
		return true;

	return false;
}

bool CollisionSystem::Circle_Circle(Position* Object1Pos, Position* Object2Pos, float Object1Hypotenuse, float Object2Hypotenuse)
{
	if (sqrtf(powf(Object1Pos->x - Object2Pos->x, 2) + powf(Object1Pos->y - Object2Pos->y, 2)) < Object1Hypotenuse + Object2Hypotenuse)
		return true;

	return false;
}

bool CollisionSystem::Circle_Square(Position* CircleCenter, Position* SquarePoint, float CircleRadius, Dimension* SquareDimension)
{
	Aux.x = CircleCenter->x;
	Aux.y = CircleCenter->y;

	if (Aux.x < SquarePoint->x)
		Aux.x = SquarePoint->x;
	else if (Aux.x - SquareDimension->Width > SquarePoint->x)
		Aux.x = SquarePoint->x + SquareDimension->Width;

	if (Aux.y < SquarePoint->y)
		Aux.y = SquarePoint->y;
	else if (Aux.y - SquareDimension->Height > SquarePoint->y)
		Aux.y = SquarePoint->y + SquareDimension->Height;

	if ((sqrtf(powf(Aux.x - CircleCenter->x, 2.0f) + powf(Aux.y - CircleCenter->y, 2.0f)) < CircleRadius))
		return true;

	return false;
}