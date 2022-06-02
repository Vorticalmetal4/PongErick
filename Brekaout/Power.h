#pragma once
#include <string>
using namespace std;


struct VectorPositionPow {
	float x;
	float y;
};


class Power {
public:
	Power(class Player* MainPlayer, class Renderer* Rend, int X, int Y);
	void Update();
	bool CheckCollition();

private:
	Player* MainPlayer;
	Renderer* Rend;
	string PowerType;
	VectorPositionPow Position;
	int Velocity;
	int Height;
	int LaserProbability;

};