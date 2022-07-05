#include "Asteroid.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>
#include <iostream>
using namespace std;

Asteroid::Asteroid(Renderer* _Rend, int x, int y, int Angle)
	:Rend(_Rend),
	Active(false),
	DeltaTime(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Width = ConFile.GetInteger("Asteroid", "Width", 1);
	Height = ConFile.GetInteger("Asteroid", "Height", 1);
	Velocity = ConFile.GetInteger("Asteroid", "Velocity", 0);
	HWidth = Width / 2;
	HHeight = Height / 2;

	FirstPoint.x = x;
	FirstPoint.y = y;

	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y + HHeight;

	FirstPoint.Angle = Angle;
	FirstPoint.Rotation = Angle * 3.141592 / 180;

	P1.x = cos(FirstPoint.Rotation) * Velocity;
	P1.y = -sin(FirstPoint.Rotation) * Velocity;

	H = sqrt(pow(Width / 2, 2) + pow(Height / 2, 2));

}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
	if(Active)
	{

		DeltaTime = Rend->getDeltaTime();

		FirstPoint.x += P1.x * DeltaTime;
		FirstPoint.y += P1.y * DeltaTime;
		Center.x = FirstPoint.x + HWidth;
		Center.y = FirstPoint.y + HHeight;

		if (FirstPoint.x > Rend->getWindowWidth())
			FirstPoint.x = 0;
		else if (FirstPoint.x < 0)
			FirstPoint.x = Rend->getWindowWidth();

		if (FirstPoint.y > Rend->getWindowHeight())
			FirstPoint.y = 0;
		else if (FirstPoint.y < 0)
			FirstPoint.y = Rend->getWindowHeight();


		Rend->DrawSimpleRect(FirstPoint.x, FirstPoint.y, Width, Height, 255, 0, 0, 255);
	}
}

bool Asteroid::CheckCollision(Asteroid* OtherAsteroid)
{
	if(sqrt(pow(Center.x - OtherAsteroid->getCenterX(), 2) + pow(Center.y - OtherAsteroid->getCenterY(), 2)) < H + OtherAsteroid->getHypotenuse())
	{
		OtherAsteroid->setActive(false);
		Active = false;
		return true;
	}
	return false;
}
