#include "Asteroid.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>
#include <iostream>

using namespace std;

Asteroid::Asteroid(Renderer* _Rend, int x, int y, int Angle)
	:Rend(_Rend),
	Active(false),
	DeltaTime(0),
	Size(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Width = ConFile.GetInteger("Asteroid", "Width", 1);
	Height = ConFile.GetInteger("Asteroid", "Height", 1);
	Velocity = ConFile.GetInteger("Asteroid", "Velocity", 0);

	UpdateData(x, y, Angle);

}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(bool Pause)
{
	if (!Pause)
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

	}

		Rend->DrawSimpleRect(FirstPoint.x, FirstPoint.y, Width, Height, 255, 0, 0, 255);
	
}

bool Asteroid::CheckCollision(Position* OtherAsteroidPos, double OtherAsteroidH)
{
	if(sqrt(pow(Center.x - OtherAsteroidPos->x, 2) + pow(Center.y - OtherAsteroidPos->y, 2)) < H + OtherAsteroidH)
		return true;
	
	return false;
}

void Asteroid::setNewData(Position* Pos, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid)
{
	Size = ParentSize + 1;
	Width = ParentWidth / 2;
	Height = ParentHeight / 2;

	if (NewAsteroid)
		UpdateData(Pos->x + Width, Pos->y - Height, Pos->Angle);
	else
		UpdateData(Pos->x - Width, Pos->y - Height, 360 - Pos->Angle);
}

void Asteroid::UpdateData(double x, double y, int Angle)
{
	HWidth = Width / 2;
	HHeight = Height / 2;

	FirstPoint.x = x;
	FirstPoint.y = y;

	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y + HHeight;

	FirstPoint.Angle = Center.Angle = Angle;
	FirstPoint.Rotation = Center.Rotation = Angle * 3.141592 / 180;

	P1.x = cos(FirstPoint.Rotation) * Velocity;
	P1.y = -sin(FirstPoint.Rotation) * Velocity;

	H = sqrt(pow(Width / 2, 2) + pow(Height / 2, 2));
}