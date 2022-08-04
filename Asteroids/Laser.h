#pragma once

#include "Renderer.h"

class Laser
{
public:
	Laser() = default;
	Laser(Renderer*  _Rend);
	~Laser();
	void Update(bool Pause);
	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setPosition(float x, float y, int _Angle, float _Rotation);
	bool CheckCollision(Position* Pos, double ObjectH);

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
	float H;
	float LifeTime;
	float TimeRemaining;

	Position P1;
	Position P2;
	Position P3;
	Position P4;
};