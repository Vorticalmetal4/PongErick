#pragma once
#include <string>
using namespace std;


struct VectorPositionPow 
{
	int x;
	int y;
};


class Power 
{
public:
	Power(class Player* MainPlayer, class Renderer* Rend, int X, int Y);
	~Power();
	void Update();
	bool CheckCollision(); // spelling -> CheckCollision

private:
	Player* MainPlayer;
	Renderer* Rend;
	string PowerType;
	VectorPositionPow Position;
	int Velocity;
	int Height;
	int LaserProbability;

};