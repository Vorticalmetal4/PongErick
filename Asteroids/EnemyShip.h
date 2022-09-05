#pragma once

#include "CommonFiles/CollisionSystem.h"
#include "Raycaster.h"

class EnemyShip
{
public: 
	EnemyShip(void) = default;
	EnemyShip(class Renderer* _Rend);
	~EnemyShip();

	bool getActive() { return Active; }
	Position* getCenter() { return &Center; }
	Dimension* getDimensions() { return &OwnDimensions; }
	float getHypotenuse() { return OwnDimensions.Hypotenuse; }

	void setActive(bool _Active) { Active = _Active; }
	void setNewData(bool Left, bool _Active);

	void Update(Position* PlayerCenter, float PlayerHypotenuse, bool Pause);
private:
	Raycaster Ray;

	Renderer* Rend;
	
	// NOTE(isaveg): Asteroid, Player, EnemyShip all use the collission system, what Object pattern reminds your? 
	// NOTE(isaveg): Duplicated code
	Position P1;
	Position P2;
	Position P3;
	Position Center;

	Dimension OwnDimensions;
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