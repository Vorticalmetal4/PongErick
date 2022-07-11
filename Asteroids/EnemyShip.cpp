#include "EnemyShip.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>

EnemyShip::EnemyShip(Renderer* _Rend)
	:Rend(_Rend),
	Active(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("EnemyShip");

	Width = ConFile.GetInteger("EnemyShip", "Width", 0);
	Height = ConFile.GetInteger("EnemyShip", "Height", 0);
	Velocity = ConFile.GetInteger("EnemyShip", "Velocity", 0);
	HWidth = Width / 2;
	HHeight = Height / 2;
	H = sqrt(pow(HHeight, 2) + pow(HWidth, 2));

	setNewData(true, false);
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::Update()
{

	Rend->DrawTriangle(&P1, &P2, &P3, 255, 0, 0, 255);
}

void EnemyShip::setNewData(bool Left, bool Active)
{
	Active = true;

	P3.y = Center.y = Rend->getWindowHeight() / 2;

	if (Left)
	{
		P1.x = P2.x = -Height;
		P3.x = 0;
		P2.y = P3.y + HWidth;
		P1.y = P3.y - HWidth;
		Center.x = P3.x - HHeight;
	}
	else
	{
		P1.x = P2.x = Rend->getWindowWidth() + Height;
		P3.x = Rend->getWindowWidth();
		P2.y = P3.y - HWidth;
		P1.y = P3.y + HWidth;
		Center.x = P3.x + HHeight;
	}
	
}