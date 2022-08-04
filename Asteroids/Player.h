#pragma once

#include <vector>
#include "Renderer.h"
#include "Laser.h"


class Player
{
public:
	Player(Renderer* _Rend);
	~Player();
	
	Position* getCenter() { return &Center; }
	float getHypotenuse() { return H; }
	float getInvincibiliy() { return Invincibility; }

	void Update(bool  Pause);
	void MovePoints(bool Rotation);
	bool CheckLasersCollisions(Position* Pos, float ObjectH);
	bool CheckCollisions(Position* Pos, float ObjectH);
	void ResetLasers();

private:
	Renderer* Rend;

	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position Center;

	int Width;
	int Height;
	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;
	int NLasers;
	int ShootCooldown;
	int CurrentCooldown;
	int Rotation;

	float H;
	float DeltaTime;
	float DamageCooldown;
	float Invincibility;

	Laser* Lasers = new Laser[NLasers];
};