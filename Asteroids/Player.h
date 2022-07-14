#pragma once

#include <vector>
#include "Renderer.h"


class Player
{
public:
	Player(Renderer* _Rend);
	~Player();
	void Update();
	void MovePoints(bool Rotation);
	bool CheckLasersCollisions(class Asteroid* CurrAsteroid);
	bool CheckLasersCollisionsWEnemies(class EnemyShip* CurrEnemy);
	bool CheckCollisionWAsteroids(Asteroid* CurrAsteroid);
	bool CheckCollisionWEnemies(EnemyShip* CurrEnemy);
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
	double H;
	float DeltaTime;
	int Velocity;
	int MaxVelocity;
	int IncVelocity;
	int DecVelocity;
	int RotationVelocity;
	std::vector<class Laser> Lasers;
	int ShootCooldown;
	int CurrentCooldown;
};