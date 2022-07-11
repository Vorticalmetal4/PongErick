#include "HUD.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;

HUD::HUD(Renderer* _Rend)
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("HUD");

	LivesInitialX = ConFile.GetInteger("HUD", "LivesInitialX", 0);
	LivesY = ConFile.GetInteger("HUD", "LivesY", 0);
	LivesWidth = ConFile.GetInteger("HUD", "LivesWidth", 0);
	LivesHeight = ConFile.GetInteger("HUD", "LivesHeight", 0);
	LivesSeparation = ConFile.GetInteger("HUD", "LivesSeparation", 0);

	LivesHWidth = LivesWidth / 2;
	LivesP1.y = LivesP3.y = LivesY + LivesHeight;
	LivesP2.y = LivesY;

	InitialPosition();

}

HUD::~HUD()
{
}

void HUD::Update(HUDData* Data)
{

	InitialPosition();

	for(i = 0; i < Data->Lives; i++)
	{
		LivesP1.x += LivesSeparation;
		LivesP2.x += LivesSeparation;
		LivesP3.x += LivesSeparation;
		Rend->DrawTriangle(&LivesP1, &LivesP2, &LivesP3, 255, 255, 255, 255);
	}
}

void HUD::InitialPosition()
{
	LivesP1.x = LivesInitialX;
	LivesP2.x = LivesInitialX + LivesHWidth;
	LivesP3.x = LivesInitialX + LivesWidth;
}