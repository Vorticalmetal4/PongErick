#include "Power.h"
#include "Player.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <string>
#include <ctime>

Power::Power(Player* _MainPlayer, Renderer* _Rend)
	:MainPlayer(_MainPlayer),
	Rend(_Rend)
{

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Power");

	Velocity = ConFile.GetInteger("Power", "Velocity", 0);
	Height = ConFile.GetInteger("Power", "Height", 0);
	LaserProbability = ConFile.GetInteger("Power", "LaserProbability", 0);
	Position.x = -50;
	Position.y = -50;
	Active = false;

}

Power::~Power() 
{

}

void Power::SetData(int _X, int _Y, bool _Active)
{
	srand(time(NULL));
	if ((rand() % (100) + 1) <= LaserProbability)
		PowerType = "L";
	else
		PowerType = "T";

	Active = _Active;
	Position.x = _X;
	Position.y = _Y;
}

void Power::Update() 
{

	NText = (char*)malloc((PowerType.size() + 1) * sizeof(char));
	PowerType.copy(NText, PowerType.size() + 1);
	NText[PowerType.size()] = '\0';
	Rend->Write(NText, 0, Height, Position.x, Position.y);
	free(NText);

}

bool Power::CheckCollision(bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();
		NPositionY = Position.y + DeltaTime * Velocity;

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
	}

	return false;
}