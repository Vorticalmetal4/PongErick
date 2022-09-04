#pragma once

#include "CollisionSystem.h"

struct AuxPosition
{
	float x;
	float y;
};

class Asteroid
{
public:
	Asteroid(void) = default;
	Asteroid(class Renderer* _Rend, float x, float y, int Angle);
	~Asteroid();

	Position* getCenter() { return &Center; }
	Position* getP1() { return &FirstPoint; }
	Dimension* getDimensions() { return &OwnDimensions; }
	int getSize() { return Size; }
	int getVelocity() { return Velocity; }
	bool getActive() { return Active; }
	float getHypotenuse() { return OwnDimensions.Hypotenuse; }
	int getAngle() { return FirstPoint.Angle; }

	void setActive(bool _Active) { Active = _Active; }
	void setSize(int _Size) { Size = _Size; }
	void setNewData(Position* Center, int ParentSize, Dimension* NewDimensions, bool NewAsteroid, int ParentVelocity);
	void setBigAsteroid(int _Width, int _Height, float x, float y, int _Velocity);
	void setLastObjectHitted(int _LastObjectHitted) { LastObjectHitted = _LastObjectHitted; }

	void ChangeDirection(int ObjectNumber);
	
	void Update(bool Pause);
	void UpdateData(float x, float y, int Angle);

private:
	Renderer* Rend;

	// NOTE(isaveg): Asteroid, Player, EnemyShip all use the collission system, what Object pattern reminds your? 
	// NOTE(isaveg): Duplicated code
	Position FirstPoint;
	Position Center;

	Dimension OwnDimensions;

	int Velocity;
	int Size;
	int LastObjectHitted;
	int SpeedIncrease;

	bool Active;

	AuxPosition P1;

	float DeltaTime;
	float HWidth;
	float HHeight;
};