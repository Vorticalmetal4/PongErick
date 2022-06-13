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
	Power(class Player* MainPlayer, class Renderer* Rend);
	~Power();
	void Update();
	bool CheckCollision(bool Pause); 
	void SetData(int _X, int _Y, bool _Active);
	bool getActive() { return Active; }

private:
	Player* MainPlayer;
	Renderer* Rend;
	string PowerType;
	VectorPositionPow Position;
	int Velocity;
	int Height;
	int LaserProbability;
	char* NText;

	float DeltaTime;
	float NPositionY;
	bool Active;

};