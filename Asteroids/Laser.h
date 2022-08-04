#pragma once

#include "Renderer.h"

class Laser
{
public:
	Laser(void) = default;
	Laser(Renderer*  _Rend);
	~Laser();

	bool getActive() { return Active; }

	void setActive(bool _Active) { Active = _Active; }
	void setPosition(float x, float y, int _Angle, float _Rotation);

	bool CheckCollision(Position* Pos, float ObjectH);
	void Update(bool Pause);

private:
	Renderer* Rend;

	Position FirstPoint;
	Position SecondPoint;
	Position ThirdPoint;
	Position FourthPoint;
	Position Center;
	Position P1;
	Position P2;
	Position P3;
	Position P4;

	bool Active;

	int Width;
	int Height;
	int Velocity;

	float DeltaTime;
	float H;
	float LifeTime;
	float TimeRemaining;

};