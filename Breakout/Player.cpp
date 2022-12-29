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
	CurrentPosition.x = (float)ConFile.GetInteger("Player", "PositionX", 1);
	CurrentPosition.y = (float)ConFile.GetInteger("Player", "PositionY", 1);
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
		MovementIncrement = PlayerVelocity * Rend->getDeltaTime();
		switch (Rend->CheckMovement()) {
		case 'R':
			CurrentPosition.x = (CurrentPosition.x + MovementIncrement + Dimensions.Width <= Rend->getWindowWidth()) ? CurrentPosition.x + MovementIncrement : CurrentPosition.x;
		break;

		case 'L':
			CurrentPosition.x = (CurrentPosition.x - MovementIncrement >= 0) ? CurrentPosition.x - MovementIncrement : CurrentPosition.x;
		break;

		case 'S':
			if (Ammo > 0 && !PlayersRay->getActive())
			{
				PlayersRay->SetData(CurrentPosition.x + Middle, CurrentPosition.y, true); 
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

	Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 178, 102, 255, 255);

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

