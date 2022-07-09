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
	int getAngle() { return Center.Angle; }
	double getCenterX() { return Center.x; }
	double getCenterY() { return Center.y; }
	double getHypotenuse() { return H; }
	int getSize() { return Size; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	void setSize(int _Size) { Size = _Size; }
	bool CheckCollision(Asteroid* OtherAsteroid);
	void setNewData(double x, double y, int Angle, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid);
	void UpdateData(double x, double y, int Angle);

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
	double H;
	int HWidth;
	int HHeight;
	int Size;

};