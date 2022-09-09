#pragma once

#include "CommonFiles/CollisionSystem.h"

class Laser
{
public:
	Laser(void) = default;
	Laser(class Renderer*  _Rend, CollisionSystem* _CollisionDetector);
	~Laser() = default;

	bool getActive() { return Active; }

	void setActive(bool _Active) { Active = _Active; }
	void setPosition(float x, float y, float _Angle, float _Rotation);

	bool CheckCollision(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare);
	void Update(bool Pause);

private:
	Renderer* Rend;

	CollisionSystem* CollisionDetector;

	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position FourthPoint;
	Position Center;
	Position P1;
	Position P2;
	Position P3;
	Position P4;

	bool Active;

	Dimension OwnDimensions;

	int Velocity;

	float DeltaTime;
	float LifeTime;
	float TimeRemaining;

};