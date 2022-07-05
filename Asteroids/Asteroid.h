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
	double getCenterX() { return Center.x; }
	double getCenterY() { return Center.y; }
	double getHypotenuse() { return H; }
	bool CheckCollision(Asteroid* OtherAsteroid);

private:
	Renderer* Rend;
	Position FirstPoint;
	Position Center;
	int Height;
	int Width;
	bool Active;
	AuxPosition P1;
	int Velocity;
	float DeltaTime;
	float H;
	int HWidth;
	int HHeight;

};