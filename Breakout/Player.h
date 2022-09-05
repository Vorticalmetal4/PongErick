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
	float getXPosition() { return ActualPosition.x; }
	float getYPosition() { return ActualPosition.y; }
	float getWidth() { return Dimensions.Width; }
	float getHeight() { return Dimensions.Height; }
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
	float Middle;
	char Power;
	class Ray* PlayersRay;

};