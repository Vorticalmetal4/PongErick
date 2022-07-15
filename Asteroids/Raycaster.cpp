#include "Raycaster.h"
#include "Renderer.h"

#include <iostream>
using namespace std;

const double Pi = 3.141592;
const double Rad = Pi / 180;

Raycaster::Raycaster(Renderer* _Rend)
	:Rend(_Rend),
	Active(false),
	DeltaTime(0),
	H(1)
{
	P1.x = P2.x = P3.x = P4.x = Center.x = -100;
	P1.y = P2.y = P3.y = P4.y = Center.y = -100;
	P1.Rotation = P2.Rotation = P3.Rotation = P4.Rotation = Center.Rotation = 0;
	P1.Angle = P2.Angle = P3.Angle = P4.Angle = Center.Angle = 0;

}

Raycaster::~Raycaster()
{
}

void Raycaster::setPosition(double x, double y, int _Angle, double _Rotation)
{
	Center.x = x;
	Center.y = y;

	Center.Angle = _Angle;
	Center.Rotation = _Rotation;

	P1.Angle = Center.Angle + 315;
	P2.Angle = Center.Angle + 45;
	P3.Angle = Center.Angle + 135;
	P4.Angle = Center.Angle + 225;


}

void Raycaster::Update(int Velocity, double x, double y)
{
	DeltaTime = Rend->getDeltaTime();

	Center.x = x;
	Center.y = y;

	H = sqrt(pow(Rend->getWindowWidth() - Center.x, 2) +  1);

	Center.x += cos(Center.Rotation) *  H;
	Center.y += -sin(Center.Rotation) * H;

	cout << Center.x << " " << Center.y << endl;

	P1.x = Center.x + cos(P1.Rotation) * H;
	P1.y = Center.y - sin(P1.Rotation) * H;
	P2.x = Center.x + cos(P2.Rotation) * H;
	P2.y = Center.y - sin(P2.Rotation) * H;
	P3.x = Center.x + cos(P3.Rotation) * H;
	P3.y = Center.y - sin(P3.Rotation) * H;
	P4.x = Center.x + cos(P4.Rotation) * H;
	P4.y = Center.y - sin(P4.Rotation) * H;

	Rend->DrawRect(&P1, &P2, &P3, &P4, 255,  0, 0, 255);
}

bool Raycaster::CheckCollision(double PlayerX, double PlayerY, double PlayerH)
{
	if(sqrt(pow(Center.x - PlayerX, 2) + pow(Center.y - PlayerY, 2)) <  H + PlayerH)
		return true;
	
	else
	{

		P1.Angle++;
		P2.Angle++;
		P3.Angle++;
		P4.Angle++;
		Center.Angle++;

		P1.Rotation = P1.Angle * Rad;
		P2.Rotation = P2.Angle * Rad;
		P3.Rotation = P3.Angle * Rad;
		P4.Rotation = P4.Angle * Rad;
		Center.Rotation = Center.Angle * Rad;

		return false;
	}
}