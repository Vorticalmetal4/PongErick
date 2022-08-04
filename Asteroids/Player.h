#pragma once

#include "CollisionSystem.h"
#include "Laser.h"


class Player
{
public:
	Player(class Renderer* _Rend, CollisionSystem* _CollisionDetector);
	~Player();

	Position* getCenter() { return &Center; }
	float getHypotenuse() { return OwnDimensions.Hypotenuse; }
	float getInvincibiliy() { return Invincibility; }

	void Update(bool  Pause);
	void MovePoints(bool Rotation);
	bool CheckLasersCollisions(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare);
	bool CheckCollisions(Position* OtherObjectPos, float OtherObjectHypotenuse);
	void ResetLasers();

private:
	Renderer* Rend;

	CollisionSystem* CollisionDetector;

	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position Center;

	Dimension OwnDimensions;

	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;
	int NLasers;
	int ShootCooldown;
	int CurrentCooldown;
	int Rotation;

	float DeltaTime;
	float DamageCooldown;
	float Invincibility;

	Laser* Lasers = new Laser[NLasers];
};