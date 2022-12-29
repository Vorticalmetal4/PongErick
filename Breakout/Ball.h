#pragma once

#include "CommonFiles/CollisionSystem.h"

struct VectorVelocity 
{
	float x;
	float y;
};

class Ball 
{
public:
	Ball(class Renderer* _Rend, CollisionSystem* CollisionDetector, class Player* _Player1);
	Position* getPosition() { return &CurrentPosition; }
	Dimension* getDimensions() { return &Dimensions; }
	float getXVelocity() { return Velocity.x; }
	void ChangeXDirection() { Velocity.x *= -1; }
	void ChangeYDirection() { Velocity.y *= -1; }
	void SetCollitionWPlayer() { CollWPlayer = false; }
	void IncXVelocity();
	void IncYVelocity();
	bool Update(bool Pause);

private:

	Renderer* Rend;
	CollisionSystem* CollisionDetector;
	Player* Player1;
	Position CurrentPosition;
	Position InitialPosition;
	Dimension Dimensions;
	VectorVelocity Velocity;

	float InitialVelocity;
	float MaxVelocity;
	int VelocityIncrease;
	bool CollWPlayer;

	float DeltaTime;
	float XInc;
	float YInc;
	float PlayerXPosition;
};