#pragma once
#include "CommonFiles/CollisionSystem.h"

class Renderer;

struct VelocityVector
{
	int x;
	int y;
};

class Ball {
public:
	Ball(Renderer* _Rend);
	void Update();

private:
	Position FirstPoint;
	Position InitialPoint;
	Renderer* Rend;
	Dimension OwnDimensions;

	VelocityVector Velocity;

	int VelocityIncrement;
	int DecreasesNumber;

	float DeltaTime;
	float IncrementX;
	float IncrementY;
};
