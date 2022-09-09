#include "Laser.h"
#include "CommonFiles/Renderer.h"
#include "Asteroid.h"
#include "Inih/cpp/INIReader.h"
#include "EnemyShip.h"

#include <corecrt_math_defines.h>
#include <cmath>

const float Rad = (float)(M_PI / 180);

Laser::Laser(Renderer* _Rend, CollisionSystem* _CollisionDetector)
	:Active(false),
	Rend(_Rend),
	DeltaTime(0),
	TimeRemaining(0),
	CollisionDetector(_CollisionDetector)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Laser: ConFile Failed");

	OwnDimensions.Width = (float)ConFile.GetInteger("Laser", "Width", 0);
	OwnDimensions.Height = (float)ConFile.GetInteger("Laser", "Height", 0);
	Velocity = ConFile.GetInteger("Laser", "Velocity", 0);
	LifeTime = float(ConFile.GetInteger("Laser", "LifeTime", 0));
	FirstPoint.x = SecondPoint.x = ThirdPoint.x = FourthPoint.x = Center.x = -100;
	FirstPoint.y = SecondPoint.y = ThirdPoint.y = FourthPoint.y = Center.y = -100;
	FirstPoint.Rotation = SecondPoint.Rotation = ThirdPoint.Rotation = FourthPoint.Rotation = Center.Rotation = 0;
	FirstPoint.Angle = SecondPoint.Angle = ThirdPoint.Angle = FourthPoint.Angle = Center.Angle = 0;
	OwnDimensions.Hypotenuse = sqrtf(powf((float)OwnDimensions.Height, 2) + powf((float)OwnDimensions.Width / 2.0f, 2)); 
	P1.x = P2.x = P3.x = P4.x = 0;
	P1.y = P2.y = P3.y = P4.y = 0;
	
}

void Laser::Update(bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();
		Center.x += cosf(Center.Rotation) * Velocity * DeltaTime; 
		Center.y -= sinf(Center.Rotation) * Velocity * DeltaTime; 
		TimeRemaining -= DeltaTime;

		if (Center.x > Rend->getWindowWidth())
			Center.x = 0;
		else if (Center.x < 0)
			Center.x = (float) Rend->getWindowWidth();

		if (Center.y > Rend->getWindowHeight())
			Center.y = 0;
		else if (Center.y < 0)
			Center.y = (float)Rend->getWindowHeight();

		FirstPoint.x = Center.x + P1.x;
		FirstPoint.y = Center.y + P1.y;
		SecondPoint.x = Center.x + P2.x;
		SecondPoint.y = Center.y + P2.y;
		ThirdPoint.x = Center.x + P3.x;
		ThirdPoint.y = Center.y + P3.y;
		FourthPoint.x = Center.x + P4.x;
		FourthPoint.y = Center.y + P4.y;
	}

	Rend->DrawRect(&FirstPoint, &SecondPoint, &ThirdPoint, &FourthPoint, 255, 255, 255, 255);

	if (TimeRemaining <= 0)
		Active = false;

}

void Laser::setPosition(float x, float y, float _Angle, float _Rotation)
{
	Center.x = x;
	Center.y = y;
	Center.Angle = _Angle;
	Center.Rotation = _Rotation;

	FirstPoint.Angle = Center.Angle + 315;
	SecondPoint.Angle = Center.Angle + 45;
	ThirdPoint.Angle = Center.Angle + 135;
	FourthPoint.Angle = Center.Angle + 225;

	FirstPoint.Rotation = FirstPoint.Angle * Rad;
	SecondPoint.Rotation = SecondPoint.Angle * Rad;
	ThirdPoint.Rotation = ThirdPoint.Angle * Rad;
	FourthPoint.Rotation = FourthPoint.Angle * Rad;

	P1.x = cosf(FirstPoint.Rotation) * OwnDimensions.Hypotenuse;
	P1.y = -sinf(FirstPoint.Rotation) * OwnDimensions.Hypotenuse;
	P2.x = cosf(SecondPoint.Rotation) * OwnDimensions.Hypotenuse;
	P2.y = -sinf(SecondPoint.Rotation) * OwnDimensions.Hypotenuse;
	P3.x = cosf(ThirdPoint.Rotation) * OwnDimensions.Hypotenuse;
	P3.y = -sinf(ThirdPoint.Rotation) * OwnDimensions.Hypotenuse;
	P4.x = cosf(FourthPoint.Rotation) * OwnDimensions.Hypotenuse;
	P4.y = -sinf(FourthPoint.Rotation) * OwnDimensions.Hypotenuse;

	TimeRemaining = LifeTime;
}

bool Laser::CheckCollision(Position* OtherObjectPos, Dimension* OtherObjectDimensions, bool isObjectASquare)
{
	if (isObjectASquare)
	{
		if (CollisionDetector->Square_Square(&FirstPoint, OtherObjectPos, &OwnDimensions, OtherObjectDimensions))
		{
			Active = false;
			return true;
		}
	}
	else
	{
		if(CollisionDetector->Circle_Circle(&Center, OtherObjectPos, OwnDimensions.Hypotenuse, OtherObjectDimensions->Hypotenuse))
		{
			Active = false;
			return true;
		}

	}

	return false;
}

