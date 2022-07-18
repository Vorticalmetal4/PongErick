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
	void Update(bool Pause);
	void setActive(bool _Active) { Active = _Active; }
	bool getActive() { return Active; }
	Position* getCenter() { return &Center; }
	double getHypotenuse() { return H; }
	int getSize() { return Size; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	void setSize(int _Size) { Size = _Size; }
	bool CheckCollision(Position* OtherAsteroidPos, double OtherAsteroidH);
	void setNewData(Position* Center, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid);
	void UpdateData(double x, double y, int Angle);
	void setBigAsteroid(int _Width, int _Height);

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