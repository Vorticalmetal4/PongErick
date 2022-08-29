#pragma once
#include "CollisionSystem.h"

class Player
{
public: 
	Player(class Renderer* _Rend);
	~Player();

	void Update();

private:
	Position Center;
	
	Renderer* Rend;

	int Radius;
	int MouthSize;
	int MouthSpeed;
	int Speed;

	float ActualMouthSize;
	float FirstMouthAngle;
	float SecondMouthAngle;
	float DeltaTime;

	int MouthIncrement;

	void AdjustMouthAngles();
};