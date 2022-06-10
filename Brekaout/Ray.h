#pragma once

#include <iostream>

struct VectorPositionRay 
{
	int x;
	int y;
};

class Ray 
{
public:
	Ray();
	~Ray();
	int getPositionX() { return Position.x; }
	int getPositionY() { return Position.y; }
	int getWidth() { return Width; }
	int getHeigth() { return Height; }
	void Move(float DeltaTime) { Position.y -= Velocity; }
	bool CheckCollition(class Brick* ActualBrick, int DeltaTime, char Power, int WindowHeight);
	void SetData(int X, int Y, bool _Active);
	bool getActive() { return Active; }
	

private:
	VectorPositionRay Position;
	int Width;
	int Height;
	int Velocity;
	bool Active;

	int NYPosition;
};