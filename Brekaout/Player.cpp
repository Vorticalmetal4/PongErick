#include "Renderer.h"
#include "Player.h"
#include "../SDL2/include/SDL.h"
#include "../Inih/cpp/INIReader.h"
#include "Ray.h"
#include "Brick.h"
#include "HUD.h"


Player::Player(Renderer* _Rend, Ray* _PlayersRay)
	:Rend(_Rend),
	PlayersRay(_PlayersRay)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

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

void Player::Update(bool Pause) {
	
	if (!Pause)
	{
		switch (Rend->CheckMovement()) {
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
				PlayersRay->SetData(Position.x + width / 2, Position.y, true); // memory leak
				Ammo--;
			}
			break;
		}

	}

	if (PlayersRay->getActive())
	{
		if(!Pause)
			PlayersRay->Move(Rend->getDeltaTime());
		Rend->DrawRect(PlayersRay->getPositionX(), PlayersRay->getPositionY(), PlayersRay->getWidth(), PlayersRay->getHeigth(), 178, 102, 255, 255);
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
	if (PlayersRay->getActive()) 
	{
		if (PlayersRay->CheckCollition(ActualBrick, Rend->getDeltaTime(), Power[0], Rend->getWindowHeight())) {
			PlayersRay->SetData(-50, -50, false);
			return true;
		}
	}
	return false;
}

