#pragma once
#include <string>
#include "CommonFiles/CollisionSystem.h"
using namespace std;

class Power 
{
public:
	Power(class Player* MainPlayer, class Renderer* Rend);
	~Power();
	void Update();
	bool CheckCollision(bool Pause); 
	void SetData(float _X, float _Y, bool _Active);
	bool getActive() { return Active; }

private:
	Player* MainPlayer;
	Renderer* Rend;
	char PowerType;
	Position ActualPosition;
	int Velocity;
	int Height;
	int LaserProbability;
	char NText[2];

	float DeltaTime;
	float NPositionY;
	bool Active;

};