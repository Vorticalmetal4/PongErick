#pragma once

#include "Renderer.h"

struct AuxPosition
{
	float x;
	float y;
};

class Asteroid
{
public:
	Asteroid(Renderer* _Rend, float x, float y, int Angle);
	~Asteroid();
	void Update(bool Pause);
	void setActive(bool _Active) { Active = _Active; }
	bool getActive() { return Active; }
	Position* getCenter() { return &Center; }
	float getHypotenuse() { return H; }
	int getSize() { return Size; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	void setSize(int _Size) { Size = _Size; }
	bool CheckCollision(Position* OtherAsteroidPos, float OtherAsteroidH);
	void setNewData(Position* Center, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid);
	void setBigAsteroid(int _Width, int _Height, float x, float y);
	void setLastObjectHited(int _LastObjectHited) { LastObjectHited = _LastObjectHited; }
	void ChangeDirection(int ObjectNumber);

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
	float HWidth;
	float HHeight;
	int Size;
	int LastObjectHited;

	void UpdateData(float x, float y, int Angle);

};