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

	bool getActive() { return Active; }
	Position* getCenter() { return &Center; }
	float getHypotenuse() { return H; }
	int getSize() { return Size; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
	int getVelocity() { return Velocity; }

	void setActive(bool _Active) { Active = _Active; }
	void setSize(int _Size) { Size = _Size; }
	void setNewData(Position* Center, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid, int ParentVelocity);
	void setBigAsteroid(int _Width, int _Height, float x, float y, int _Velocity);
	void setLastObjectHitted(int _LastObjectHitted) { LastObjectHitted = _LastObjectHitted; }

	bool CheckCollision(Position* OtherAsteroidPos, float OtherAsteroidH);
	void ChangeDirection(int ObjectNumber);
	
	void Update(bool Pause);

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
	int LastObjectHitted;
	int SpeedIncrease;

	void UpdateData(float x, float y, int Angle);

};