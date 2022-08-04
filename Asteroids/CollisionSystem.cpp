#include "CollisionSystem.h"

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

bool CollisionSystem::Square_Circle(Position* CirclePos)
{

}