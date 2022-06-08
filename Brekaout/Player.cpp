#include "Renderer.h"
#include "Player.h"
#include "../SDL2/include/SDL.h"
#include "../Inih/cpp/INIReader.h"
#include "Ray.h"
#include "Brick.h"

#include <iostream>
#include <vector>

using namespace std;

Player::Player(Renderer* _Rend)
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Player: Couldn't find the Configuration File" << endl;

	PlayerVelocity = ConFile.GetInteger("Player", "PlayerVelocity", -1);
	Position.x = ConFile.GetInteger("Player", "PositionX", 1);
	Position.y = ConFile.GetInteger("Player", "PositionY", 1);
	width = ConFile.GetInteger("Player", "Width", 80);
	height = ConFile.GetInteger("Player", "Height", 20);

	Power = "No power";
	Ammo = 0;


}

Player::~Player()
{

}

void Player::Update() {
	
	switch(Rend->CheckMovement()) {
		case 'R':
			if (Position.x + (PlayerVelocity * Rend->getDeltaTime() + width) <= Rend->getWindowWidth())
				Position.x += PlayerVelocity * Rend->getDeltaTime();
		break;

		case 'L':
			if (Position.x - PlayerVelocity * Rend->getDeltaTime() >= 0)
				Position.x -= PlayerVelocity * Rend->getDeltaTime();
		break;

		case 'P':
			if (Ammo > 0)
			{
				Ray* NRay = new Ray(Position.x + width / 2, Position.y); // memory leak
				Rays.push_back(NRay);
				Ammo--;
			}
		break;
	}
	


	if (Rays.size() > 0)
	{
		for (int i = 0; i < Rays.size(); i++) 
		{
			Rays[i]->Move(Rend->getDeltaTime());
			Rend->DrawRect(Rays[i]->getPositionX(), Rays[i]->getPositionY(), Rays[i]->getWidth(), Rays[i]->getHeigth(), 178, 102, 255, 255);
		}
	}


	Rend->DrawRect(Position.x, Position.y, width, height, 178, 102, 255, 255);

}

void Player::ChangePower(string NPower) 
{
	Power = NPower;
	Ammo = 1;
}

bool Player::CheckLasersCollition(Brick* ActualBrick)
{
	for (int i = 0; i < Rays.size(); i++)
	{
		if (Rays[i]->CheckCollition(ActualBrick, Rend->getDeltaTime(), Power[0], Rend->getWindowHeight())) {
			Rays[i]->~Ray();
			Rays.erase(Rays.begin() + i);
			if (Ammo == 0)
				Power = "No Power";
			return true;
		}
	}
	return false;
}

