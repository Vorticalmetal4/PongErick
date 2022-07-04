#include "Asteroid.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>

Asteroid::Asteroid(Renderer* _Rend, int x, int y, int Angle)
	:Rend(_Rend),
	Active(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Width = ConFile.GetInteger("Asteroid", "Width", 1);
	Height = ConFile.GetInteger("Asteroid", "Height", 1);
	Velocity = ConFile.GetInteger("Asteroid", "Velocity", 0);
	HWidth = Width / 2;
	HHeigth = Height / 2;

	FirstPoint.x = x;
	FirstPoint.y = y;

	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y - HHeigth;

	FirstPoint.Angle = Center.Angle = Angle;
	FirstPoint.Rotation = Center.Rotation = Angle * 3.141592 / 180;

	P1.x = cos(FirstPoint.Rotation) * Velocity;
	P1.y = -sin(FirstPoint.Rotation) * Velocity;

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
		Center.x += P1.x * DeltaTime;
		Center.y += P1.y * DeltaTime;

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