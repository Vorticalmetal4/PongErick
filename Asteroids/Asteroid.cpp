#include "Asteroid.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Unity/src/unity.h"

#include <cmath>
#include <iostream>




const float Pi = (float)3.141592;
const float Rad = Pi / 180;

Asteroid::Asteroid(Renderer* _Rend, float x, float y, int Angle)
	:Rend(_Rend),
	Active(false),
	DeltaTime(0),
	Size(0),
	LastObjectHitted(-1)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Player");

	Width = ConFile.GetInteger("Asteroid", "Width", 1);
	Height = ConFile.GetInteger("Asteroid", "Height", 1);
	Velocity = ConFile.GetInteger("Asteroid", "Velocity", 0);
	SpeedIncrease = ConFile.GetInteger("Asteroid", "SpeedIncrease", 0);

	UpdateData(x, y, Angle);

}

Asteroid::~Asteroid()
{
}

void Asteroid::setBigAsteroid(int _Width, int _Height, float x, float y, int _Velocity)
{
	Active = true;
	Size = 0;
	Width = _Width;
	Height = _Height;
	FirstPoint.x = x;
	FirstPoint.y = y;
	LastObjectHitted = -1;
	Velocity = _Velocity;
	P1.x = cosf(FirstPoint.Rotation) * Velocity;
	P1.y = -sinf(FirstPoint.Rotation) * Velocity;
		
	H = sqrtf(powf(Width / 2.0f, 2) + powf(Height / 2.0f, 2));
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

		if (FirstPoint.x + Width >= Rend->getWindowWidth())
		{
			FirstPoint.x = Rend->getWindowWidth() - Width - 1.0f;
			ChangeDirection(0);
		}
		else if (FirstPoint.x <= 0)
		{
			FirstPoint.x = 1;
			ChangeDirection(2);
		}

		if (FirstPoint.y + Height >= Rend->getWindowHeight())
		{
			FirstPoint.y = Rend->getWindowHeight() - Height - 1.0f;
			ChangeDirection(1);
		}
		else if (FirstPoint.y <= 0)
		{
			FirstPoint.y = 1;
			ChangeDirection(3);
		}

		if (Center.x > Rend->getWindowWidth() || Center.x < 0 || Center.y < 0 || Center.y > Rend->getWindowHeight())
			LastObjectHitted = -1;
	

	}
		Rend->DrawSimpleRect(FirstPoint.x, FirstPoint.y, Width, Height, 255, 0, 0, 255);
}

bool Asteroid::CheckCollision(Position* OtherAsteroidPos, int OtherAsteroidHeight, int OtherAsteroidWidth)
{
	if (FirstPoint.x + Width > OtherAsteroidPos->x && FirstPoint.x < OtherAsteroidPos->x + OtherAsteroidWidth && FirstPoint.y + Height > OtherAsteroidPos->y && FirstPoint.y < OtherAsteroidPos->y + OtherAsteroidHeight )
		return true;

	return false;
}

void Asteroid::setNewData(Position* Pos, int ParentSize, int ParentWidth, int ParentHeight, bool NewAsteroid, int ParentVelocity)
{
	Size = ParentSize + 1;
	Width = ParentWidth / 2;
	Height = ParentHeight / 2;
	Velocity = ParentVelocity + SpeedIncrease;

	if (NewAsteroid)
		UpdateData(Pos->x + Width, Pos->y - Height, Pos->Angle);
	else
		UpdateData(Pos->x - Width, Pos->y - Height, 360 - Pos->Angle);
}

void Asteroid::UpdateData(float x, float y, int Angle)
{

	HWidth = Width / 2.0f;
	HHeight = Height / 2.0f;

	FirstPoint.x = x;
	FirstPoint.y = y;

	if (FirstPoint.x <= 1)
		FirstPoint.x += Width;
	else if (FirstPoint.x >= Rend->getWindowWidth())
		FirstPoint.x -= Width;

	if (FirstPoint.y <= 1)
		FirstPoint.y += Height;
	else if (FirstPoint.y >= Rend->getWindowHeight())
		FirstPoint.y -= Height;

	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y + HHeight;

	FirstPoint.Angle = Center.Angle = Angle;
	FirstPoint.Rotation = Center.Rotation = Angle * Rad;

	P1.x = cosf(FirstPoint.Rotation) * Velocity; 
	P1.y = -sinf(FirstPoint.Rotation) * Velocity; 

	H = sqrtf(powf(Width / 2.0f, 2) + powf(Height / 2.0f, 2));

}

void Asteroid::ChangeDirection(int ObjectNumber)
{
	if (ObjectNumber != LastObjectHitted)
	{
		FirstPoint.Angle += 180;
		FirstPoint.Rotation = FirstPoint.Angle * Rad;
		P1.x = cosf(FirstPoint.Rotation) * Velocity;
		P1.y = -sinf(FirstPoint.Rotation) * Velocity;
		LastObjectHitted = ObjectNumber;
	}

}