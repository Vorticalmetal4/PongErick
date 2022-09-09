#pragma once

#include "CommonFiles/CollisionSystem.h"
#include "Raycaster.h"
#include "CommonFiles/Triangle.h"

class EnemyShip
{
public:
	EnemyShip() = default;
	EnemyShip(class Renderer* _Rend);
	~EnemyShip() = default;

	bool getActive() { return Active; }
	Position* getCenter() { return Body.getCenter(); }
	Dimension* getDimensions() { return Body.getDimensions(); }
	float getHypotenuse() { return Body.getDimensions()->Hypotenuse; }

	void setActive(bool _Active) { Active = _Active; }
	void setNewData(bool Left, bool _Active);

	void Update(Position* PlayerCenter, float PlayerHypotenuse, bool Pause);
private:
	Raycaster Ray;

	Renderer* Rend;
	
	// NOTE(isaveg): Asteroid, Player, EnemyShip all use the collission system, what Object pattern reminds your? 

	Triangle Body;
	Position* BodyCenter;
	Position* BodyThirdPoint;

	int Velocity;

	float HWidth;
	float HHeight;
	float DeltaTime;

	bool wasPlayerUp;
	bool wasPlayerLeft;
	bool ChangeDirection;
	bool TurnLeft;
	bool Active;
};