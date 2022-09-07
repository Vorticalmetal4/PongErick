#pragma once

#include "CommonFiles/CollisionSystem.h"
#include "CommonFiles/Triangle.h"
#include "Laser.h"

class Player
{
public:
	Player(class Renderer* _Rend, CollisionSystem* _CollisionDetector);
	~Player();

	Position* getCenter() { return Body.getCenter(); }
	float getHypotenuse() { return Body.getDimensions()->Hypotenuse; }
	float getInvincibiliy() { return Invincibility; }

	void Update(bool  Pause);
	void ResetLasers();
	bool CheckLasersCollisions(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare);
	bool CheckCollisions(Position* OtherObjectPos, float OtherObjectHypotenuse);

private:
	Renderer* Rend;

	CollisionSystem* CollisionDetector;

	// NOTE(isaveg): Asteroid, Player, EnemyShip all use the collission system, what Object pattern reminds your? 

	Triangle Body;

	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;
	int NLasers;
	int ShootCooldown;
	int CurrentCooldown;

	float Rotation;
	float DeltaTime;
	float DamageCooldown;
	float Invincibility;

	Laser* Lasers;
};