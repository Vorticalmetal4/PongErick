#pragma once

#include <vector>
#include "Renderer.h"
#include "Laser.h"


class Player
{
public:
	Player(Renderer* _Rend);
	~Player();
	void Update(bool  Pause);
	void MovePoints(bool Rotation);
	bool CheckLasersCollisions(Position* Pos, double ObjectH);
	bool CheckCollisions(Position* Pos, double ObjectH);
	Position* getCenter() { return &Center; }
	double getHypotenuse() { return H; }

private:
	Renderer* Rend;
	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position Center;
	int Width;
	int Height;
	float H;
	float DeltaTime;
	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;
	std::vector<Laser> Lasers;
	int ShootCooldown;
	int CurrentCooldown;
	float DamageCooldown;
	float Invincibility;
};