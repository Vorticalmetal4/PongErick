#pragma once

#include "Renderer.h"

/*struct AuxPosition
{
	double x;
	double y;
};*/

class Laser
{
public:
	Laser(Renderer*  _Rend);
	~Laser();
	void Update();
	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setPosition(double x, double y, int _Angle, double _Rotation);
	bool CheckCollision(class Asteroid* CurrAsteroid);

private:
	Renderer* Rend;
	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position FourthPoint;
	Position Center;
	bool Active;
	int Width;
	int Height;
	int Velocity;
	float DeltaTime;
	double H;
	int LifeTime;
	float TimeRemaining;

	Position P1;
	Position P2;
	Position P3;
	Position P4;
};