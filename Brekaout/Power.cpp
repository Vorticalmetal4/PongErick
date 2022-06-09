#include "Power.h"
#include "Player.h"
#include "Renderer.h"
#include "../Inih/cpp/INIReader.h"

#include <string>
#include <ctime>

Power::Power(Player* _MainPlayer, Renderer* _Rend, int _X, int _Y)
	:MainPlayer(_MainPlayer),
	Rend(_Rend)
{

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Power");

	Velocity = ConFile.GetInteger("Power", "Velocity", 0);
	Height = ConFile.GetInteger("Power", "Height", 0);
	LaserProbability = ConFile.GetInteger("Power", "LaserProbability", 0);
	Position.x = _X;
	Position.y = _Y;


	srand(time(NULL));
	if ((rand() % (100) + 1) <= LaserProbability) 
		PowerType = "L";
	else
		PowerType = "T";

}

Power::~Power() 
{

}

void Power::Update() 
{
	NText = new char[PowerType.size() + 1]; // memory leak
	PowerType.copy(NText, PowerType.size() + 1);
	NText[PowerType.size()] = '\0';
	Rend->Write(NText, 0, Height, Position.x, Position.y);

}

bool Power::CheckCollision()
{

	float DeltaTime = Rend->getDeltaTime();
	float NPositionY = Position.y + DeltaTime * Velocity;

	if (NPositionY + Height <= Rend->getWindowHeight())
	{
		if (Position.x >= MainPlayer->getXPosition() && Position.x <= MainPlayer->getXPosition() + MainPlayer->getWidth())
		{
			if (NPositionY + Height >= MainPlayer->getYPosition() && NPositionY + Height <= MainPlayer->getYPosition() + MainPlayer->getHeight())
			{
				MainPlayer->ChangePower(PowerType);
				return true;
			}
			else
				Position.y = NPositionY;
		}
		else
			Position.y = NPositionY;
	}
	else
		return true;

	return false;
}