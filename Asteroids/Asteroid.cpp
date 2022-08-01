#include "Asteroid.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>

const float Pi = (float)3.141592;
const float Rad = Pi / 180;

Asteroid::Asteroid(Renderer* _Rend, float x, float y, int Angle)
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

void Asteroid::setBigAsteroid(int _Width, int _Height)
{
	Active = true;
	Size = 0;
	Width = _Width;
	Height = _Height;
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

		if (FirstPoint.x > Rend->getWindowWidth())
			FirstPoint.x = 0;
		else if (FirstPoint.x < 0)
			FirstPoint.x = (float)Rend->getWindowWidth();

		if (FirstPoint.y > Rend->getWindowHeight())
			FirstPoint.y = 0;
		else if (FirstPoint.y < 0)
			FirstPoint.y = (float)Rend->getWindowHeight();

	}
		Rend->DrawSimpleRect(FirstPoint.x, FirstPoint.y, Width, Height, 255, 0, 0, 255);
}

bool Asteroid::CheckCollision(Position* OtherAsteroidPos, double OtherAsteroidH)
{
	if(sqrtf(powf(Center.x - OtherAsteroidPos->x, 2) + powf(Center.y - OtherAsteroidPos->y, 2)) < H + OtherAsteroidH)
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

void Asteroid::UpdateData(float x, float y, int Angle)
{
	HWidth = Width / 2;
	HHeight = Height / 2;

	FirstPoint.x = x;
	FirstPoint.y = y;

	Center.x = FirstPoint.x + HWidth;
	Center.y = FirstPoint.y + HHeight;

	FirstPoint.Angle = Center.Angle = Angle;
	FirstPoint.Rotation = Center.Rotation = Angle * Rad;

	P1.x = cosf(FirstPoint.Rotation) * Velocity; 
	P1.y = -sinf(FirstPoint.Rotation) * Velocity; 

	H = sqrtf(powf(Width / 2.0f, 2) + powf(Height / 2.0f, 2));
}