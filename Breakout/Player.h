#pragma once
#include <iostream>
#include <vector>
#include "CommonFiles/CollisionSystem.h"

using namespace std;

class Player 
{
public:
	Player(class Renderer* Rend, class Ray* _PlayersRay);
	~Player();
	void Update(bool Pause);
	int getXPosition() { return ActualPosition.x; }
	int getYPosition() { return ActualPosition.y; }
	int getWidth() { return Dimensions.Width; }
	int getHeight() { return Dimensions.Height; }
	void ChangePower(char NPower);
	char getPower() { return Power; }
	void NoPower() { Power = 'N'; }
	bool CheckLasersCollition(class Brick* ActualBrick);

private:

	Renderer* Rend;
	int PlayerVelocity;
	Position ActualPosition;
	Dimension Dimensions;
	int Ammo;
	int Middle;
	char Power;
	class Ray* PlayersRay;

};