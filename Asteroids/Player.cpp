#include "Player.h"
#include "Inih/cpp/INIReader.h"
#include "Renderer.h"

Player::Player(Renderer* _Rend) 
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Velocity.x = Velocity.y = ConFile.GetInteger("Player", "PlayerVelocity", 0);
	Width = ConFile.GetInteger("Player", "Width", 0);
	Height = ConFile.GetInteger("Player", "Height", 0);
	FirstPoint.x = ConFile.GetInteger("Player", "PositionX", 0);
	FirstPoint.y =  SecondPoint.y = ConFile.GetInteger("Player", "PositionY", 0);
	SecondPoint.x = FirstPoint.x + Width;
	ThirdPoint.x = FirstPoint.x + Width / 2;
	ThirdPoint.y = FirstPoint.y - Height;
}

Player::~Player()
{
}

void Player::Update()
{
	Rend->DrawTriangle(FirstPoint.x, FirstPoint.y, SecondPoint.x, SecondPoint.y, ThirdPoint.x, ThirdPoint.y 255, 255, 255, 255);
}