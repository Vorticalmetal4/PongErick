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
	Ball(class Renderer* _Rend, class Player* _Player1);
	float getXPosition() { return ActualPosition.x; }
	float getYPosition() { return ActualPosition.y; }
	float getXVelocity() { return Velocity.x; }
	float getHeight() { return Dimensions.Height; }
	float getWidth() { return Dimensions.Width; }
	void ChangeXDirection() { Velocity.x *= -1; }
	void ChangeYDirection() { Velocity.y *= -1; }
	void SetCollitionWPlayer() { CollWPlayer = false; }
	void IncXVelocity();
	void IncYVelocity();
	bool Update(bool Pause);

private:

	Renderer* Rend;
	Player* Player1;
	Position ActualPosition;
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