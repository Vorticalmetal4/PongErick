#include "Laser.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

#include <cmath>
#include <iostream>

using namespace std;

const double Pi = 3.141592;
const double Rad = Pi / 180;

Laser::Laser(Renderer* _Rend)
	:Active(false),
	Rend(_Rend),
	DeltaTime(0)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Laser");

	Width = ConFile.GetInteger("Laser", "Width", 0);
	Height = ConFile.GetInteger("Laser", "Height", 0);
	Velocity = ConFile.GetInteger("Laser", "Velocity", 0);
	FirstPoint.x = SecondPoint.x = ThirdPoint.x = FourthPoint.x = Center.x = -100;
	FirstPoint.y = SecondPoint.y = ThirdPoint.y = FourthPoint.y = Center.y = -100;
	FirstPoint.Rotation = SecondPoint.Rotation = ThirdPoint.Rotation = FourthPoint.Rotation = Center.Rotation = 0;
	FirstPoint.Angle = SecondPoint.Angle = ThirdPoint.Angle = FourthPoint.Angle = Center.Angle = 0;
	H = sqrt(pow(Height, 2) + pow(Width / 2, 2));
}

Laser::~Laser()
{
}

void Laser::Update()
{
	if (Active)
	{
		DeltaTime = Rend->getDeltaTime();
		Center.x += cos(Center.Rotation) * Velocity * DeltaTime;
		Center.y -= sin(Center.Rotation) * Velocity * DeltaTime;

		FirstPoint.x = Center.x + cos(FirstPoint.Rotation) * H;
		FirstPoint.y = Center.y - sin(FirstPoint.Rotation) * H;
		SecondPoint.x = Center.x + cos(SecondPoint.Rotation) * H;
		SecondPoint.y = Center.y - sin(SecondPoint.Rotation) * H;
		ThirdPoint.x = Center.x + cos(ThirdPoint.Rotation) * H;
		ThirdPoint.y = Center.y - sin(ThirdPoint.Rotation) * H;
		FourthPoint.x = Center.x + cos(FourthPoint.Rotation) * H;
		FourthPoint.y = Center.y - sin(FourthPoint.Rotation) * H;

		Rend->DrawRect(&FirstPoint, &SecondPoint, &ThirdPoint, &FourthPoint, 255, 255, 255, 255);
	}
}

void Laser::setPosition(double x, double y, int _Angle, double _Rotation)
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
}