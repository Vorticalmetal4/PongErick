#include "Power.h"
#include "Player.h"
#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <string>
#include <ctime>

Power::Power(Player* _MainPlayer, Renderer* _Rend)
	:MainPlayer(_MainPlayer),
	Rend(_Rend),
	DeltaTime(0),
	NPositionY(0),
	Active(false)
{

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Power could not find ConFile");

	Velocity = ConFile.GetInteger("Power", "Velocity", 0);
	Height = ConFile.GetInteger("Power", "Height", 0);
	LaserProbability = ConFile.GetInteger("Power", "LaserProbability", 0);

	ActualPosition.x = -50;
	ActualPosition.y = -50;

	NText[0] = ' ';
	PowerType = ' ';
}

Power::~Power() 
{

}

void Power::SetData(float _X, float _Y, bool _Active)
{
	srand((unsigned int)time(NULL));
	if ((rand() % (100) + 1) <= LaserProbability) 
		PowerType = 'L';
	else
		PowerType = 'T';
		

	Active = _Active;
	ActualPosition.x = _X;
	ActualPosition.y = _Y;
}

void Power::Update() 
{
	NText[0] = PowerType;
	NText[1] = '\0';
	Rend->Write(NText, 0, Height, ActualPosition.x, ActualPosition.y);

}

bool Power::CheckCollision(bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();
		NPositionY = ActualPosition.y + DeltaTime * Velocity;

		if (NPositionY + Height <= Rend->getWindowHeight())
		{
			if (ActualPosition.x >= MainPlayer->getPosition()->x && ActualPosition.x <= MainPlayer->getPosition()->x + MainPlayer->getWidth())
			{
				if (NPositionY + Height >= MainPlayer->getPosition()->y && NPositionY + Height <= MainPlayer->getPosition()->y + MainPlayer->getHeight())
				{
					MainPlayer->ChangePower(PowerType);
					return true;
				}
				else
					ActualPosition.y = NPositionY;
			}
			else
				ActualPosition.y = NPositionY;
		}
		else
			return true;
	}

	return false;
}