#pragma once

#include "Renderer.h"

struct AuxPosition
{
	double x;
	double y;
};

class Asteroid
{
public:
	Asteroid(Renderer* _Rend, int x, int y, int Angle);
	~Asteroid();
	void Update();
	void setActive(bool _Active) { Active = _Active; }
	bool getActive() { return Active; }

private:
	Renderer* Rend;
	Position FirstPoint;
	int Height;
	int Width;
	bool Active;
	AuxPosition P1;
	int Velocity;
	float DeltaTime;

};