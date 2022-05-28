#pragma once
#include <string>
using namespace std;


struct VectorPositionPow {
	float x;
	float y;
};


class Power {
public:
	Power(class Player* MainPlayer, int VectorPosition, class Renderer* Rend, int X, int Y);
	void Update();
	bool CheckCollition();

private:
	Player* MainPlayer;
	Renderer* Rend;
	string PowerType;
	int VectorPosition;
	VectorPositionPow Position;
	int Velocity;
	int Height;

};