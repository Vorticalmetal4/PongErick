#pragma once

#include <iostream>
#include "CommonFiles/CollisionSystem.h"

class Ray 
{
public:
	Ray();
	~Ray();
	Position* getPosition() { return &ActualPosition; }
	Dimension* getDimensions() { return &Dimensions; }
	void Move(float DeltaTime) { ActualPosition.y -= Velocity; }
	bool CheckCollition(class Brick* ActualBrick, float DeltaTime, char Power, int WindowHeight);
	void SetData(float X, float Y, bool _Active);
	bool getActive() { return Active; }
	

private:
	Position ActualPosition;
	Dimension Dimensions;
	int Velocity;
	bool Active;

	float NYPosition;
};