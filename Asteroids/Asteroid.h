#pragma once

#include "CommonFiles/CollisionSystem.h"
#include <ctime>

struct AuxPosition
{
	float x;
	float y;
};

class Asteroid
{
public:
	Asteroid(void) = default;
	Asteroid(class Renderer* _Rend, float x, float y, float Angle);
	~Asteroid() = default;

	Position* getCenter() { return &Center; }
	Position* getP1() { return &FirstPoint; }
	Dimension* getDimensions() { return &OwnDimensions; }
	int getSize() { return Size; }
	int getVelocity() { return Velocity; }
	float getAngle() { return FirstPoint.Angle; }
	bool getActive() { return Active; }
	float getHypotenuse() { return OwnDimensions.Hypotenuse; }

	void setActive(bool _Active) { Active = _Active; }
	void setSize(int _Size) { Size = _Size; }
	void setNewData(Position* Center, int ParentSize, Dimension* NewDimensions, bool NewAsteroid, int ParentVelocity);
	void setBigAsteroid(float _Width, float _Height, float x, float y, int _Velocity);
	void setLastObjectHitted(int _LastObjectHitted) { LastObjectHitted = _LastObjectHitted; }

	void ChangeDirection(int ObjectNumber);
	
	void Update(bool Pause, tm* CurrentTime);
	void UpdateData(float x, float y, float Angle);

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
	int i;
	int ClockHandsNumber;

	bool Active;

	AuxPosition P1;

	float DeltaTime;
	float HWidth;
	float HHeight;

	class ClockHand* ClockHands;
};