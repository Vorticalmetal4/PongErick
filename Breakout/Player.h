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
	Position* getPosition() { return &CurrentPosition; }
	Dimension* getDimensions() { return &Dimensions; }
	float getWidth() { return Dimensions.Width; }
	float getHeight() { return Dimensions.Height; }
	void ChangePower(char NPower);
	char getPower() { return Power; }
	void NoPower() { Power = 'N'; }
	bool CheckLasersCollition(class Brick* ActualBrick);

private:

	Renderer* Rend;
	Position CurrentPosition;
	Dimension Dimensions;
	int PlayerVelocity;
	int Ammo;
	float Middle;
	float MovementIncrement;
	char Power;
	class Ray* PlayersRay;

};