#include "CommonFiles/Renderer.h"
#include "Player.h"
#include "SDL2/include/SDL.h"
#include "Inih/cpp/INIReader.h"
#include "Ray.h"
#include "Brick.h"
#include "HUD.h"

#include <iostream>
using namespace std;

Player::Player(Renderer* _Rend, Ray* _PlayersRay)
	:Rend(_Rend),
	PlayersRay(_PlayersRay),
	Power('N'),
	Ammo(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	PlayerVelocity = ConFile.GetInteger("Player", "PlayerVelocity", -1);
	ActualPosition.x = (float)ConFile.GetInteger("Player", "PositionX", 1);
	ActualPosition.y = (float)ConFile.GetInteger("Player", "PositionY", 1);
	Dimensions.Width = (float)ConFile.GetInteger("Player", "Width", 80);
	Dimensions.Height = (float)ConFile.GetInteger("Player", "Height", 20);

	Middle = Dimensions.Width / 2.0f;

}

Player::~Player()
{

}

void Player::Update(bool Pause) {
	
	if (!Pause)
	{
		switch (Rend->CheckMovement()) {
		case 'R':
			if (ActualPosition.x + (PlayerVelocity * Rend->getDeltaTime() + Dimensions.Width) <= Rend->getWindowWidth())
				ActualPosition.x += PlayerVelocity * Rend->getDeltaTime();
			break;

		case 'L':
			if (ActualPosition.x - PlayerVelocity * Rend->getDeltaTime() >= 0)
				ActualPosition.x -= PlayerVelocity * Rend->getDeltaTime();
			break;

		case 'S':
			if (Ammo > 0 && !PlayersRay->getActive())
			{
				cout << "Player has shooted" << endl;
				PlayersRay->SetData(ActualPosition.x + Middle, ActualPosition.y, true); 
				Ammo--;
			}
			break;
		}

	}

	if (PlayersRay->getActive())
	{
		if(!Pause)
			PlayersRay->Move(Rend->getDeltaTime());
		Rend->DrawSimpleRect(PlayersRay->getPosition(), PlayersRay->getDimensions(), 178, 102, 255, 255);
	}

	Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 178, 102, 255, 255);

}

void Player::ChangePower(char NPower) 
{
	Power = NPower;
	Ammo = 1;
}

bool Player::CheckLasersCollition(Brick* ActualBrick)
{
	if (PlayersRay->getActive()) 
	{
		if (PlayersRay->CheckCollition(ActualBrick, Rend->getDeltaTime(), Power, Rend->getWindowHeight())) 
		{
			PlayersRay->SetData(-50, -50, false);
			return true;
		}
	}
	return false;
}

