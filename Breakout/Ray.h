#pragma once

#include <iostream>
#include "CommonFiles/CollisionSystem.h"

class Ray 
{
public:
	Ray(CollisionSystem* _CollisionDetector);
	~Ray();
	Position* getPosition() { return &CurrentPosition; }
	Dimension* getDimensions() { return &Dimensions; }
	void Move(float DeltaTime) { CurrentPosition.y -= Velocity; }
	bool CheckCollition(class Brick* ActualBrick, float DeltaTime, char Power, int WindowHeight);
	void SetData(float X, float Y, bool _Active);
	bool getActive() { return Active; }
	

private:
	Position CurrentPosition;
	CollisionSystem* CollisionDetector;
	Dimension Dimensions;
	int Velocity;
	bool Active;

	float NYPosition;
};