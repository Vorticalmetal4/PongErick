#pragma once
#include "CollisionSystem.h"

class Player
{
public: 
	Player(class Renderer* _Rend);
	~Player();

	void Update();

private:
	Position P1;
	Renderer* Rend;
};