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
	if ( (Object1Pos->x + Object1Dim->Width > Object2Pos->x) && (Object1Pos->x < Object2Pos->x + Object2Dim->Width) && (Object1Pos->y + Object1Dim->Height > Object2Pos->y) && (Object1Pos->y < Object2Pos->y + Object2Dim->Height) )
		return true;

	return false;
}

bool CollisionSystem::Circle_Circle(Position* Object1Pos, Position* Object2Pos, float Object1Hypotenuse, float Object2Hypotenuse)
{
	if (sqrtf(powf(Object1Pos->x - Object2Pos->x, 2) + powf(Object1Pos->y - Object2Pos->y, 2)) < Object1Hypotenuse + Object2Hypotenuse)
		return true;

	return false;
}
