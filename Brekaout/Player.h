#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct VectorPosition 
{
	int x;
	int y;
};

class Player 
{
public:
	Player(class Renderer* Rend);
	~Player();
	void Update();
	int getXPosition() { return Position.x; }
	int getYPosition() { return Position.y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	void ChangePower(string NPower);
	string getPower() { return Power; }
	void setPower(string NPower) { Power = NPower; }
	bool CheckLasersCollition(class Brick* ActualBrick);

private:

	Renderer* Rend;
	int PlayerVelocity;
	VectorPosition Position;
	int width;
	int height;
	int Ammo;
	string Power;
	class Ray* PlayersRay;

};