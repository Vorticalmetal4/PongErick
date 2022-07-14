#include "EnemyShip.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Raycaster.h"

#include <cmath>
#include <iostream>
using namespace std;

const double Pi = 3.141592;
const double Rad = Pi / 180;

EnemyShip::EnemyShip(Renderer* _Rend)
	:Rend(_Rend),
	Active(false),
	Ray(_Rend)
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

void EnemyShip::Update(Position* PlayerCenter, double PlayerHypotenuse)
{
	DeltaTime = Rend->getDeltaTime();

	//AngleRotation = acos((Center.x * PlayerCenter->x + (Rend->getWindowHeight() - Center.y) * (Rend->getWindowHeight() - PlayerCenter->y)) / (sqrt(pow(Center.x, 2) + pow((Rend->getWindowHeight() - Center.y), 2)) * sqrt(pow(PlayerCenter->x, 2) + pow((Rend->getWindowHeight() - PlayerCenter->y), 2)))) * (180 / Pi) > 20
	//Center.Angle = P3.Angle = acos((4 * 2 + -1 * 5) / (sqrt(pow(4, 2) + pow(-1, 2)) * sqrt(pow(2, 2) + pow(5, 2)))) * (180 / Pi);
	/*double n = (4 * 2 + (-1) * 5) / (sqrt(pow(4, 2) + pow(-1, 2)) * sqrt(pow(2, 2) + pow(5, 2)));*/
	//cout << Center.x << " " << Rend->getWindowHeight()  - Center.y << " Player " << PlayerCenter->x << " " << Rend->getWindowHeight() - PlayerCenter->y << endl;

	if (!Ray.CheckCollision(PlayerCenter->x, PlayerCenter->y, PlayerHypotenuse))
	{
		P1.Angle++;
		P2.Angle++;
		P3.Angle++;
		Center.Angle++;
	}

	Ray.Update(Velocity);

	P1.Rotation = P1.Angle * Rad;
	P2.Rotation = P2.Angle * Rad;
	Center.Rotation = P3.Rotation = Center.Angle * Rad;

	P3.x = Center.x + cos(P3.Rotation) * H;
	P3.y = Center.y - sin(P3.Rotation) * H;
	P2.x = Center.x + cos(P2.Rotation) * H;
	P2.y = Center.y - sin(P2.Rotation) * H;
	P1.x = Center.x + cos(P1.Rotation) * H;
	P1.y = Center.y - sin(P1.Rotation) * H;
	Rend->DrawTriangle(&P1, &P2, &P3, 255, 0, 0, 255);
}

void EnemyShip::setNewData(bool Left, bool _Active)
{
	Active = _Active;
	Ray.setActive(true);
	Ray.setPosition(P3.x, P3.y, P3.Angle, P3.Rotation);

	P3.y = Center.y = Rend->getWindowHeight() / 2;

	/*if (Left)
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
	}*/

	P1.x = Rend->getWindowWidth() / 2;
	P2.x = P1.x + Width;
	P3.x = Center.x = P1.x + HWidth;

	P1.y = P2.y = Rend->getWindowHeight() / 2;
	P3.y = P1.y - Height;

	P3.Angle = Center.Angle = 0;
	P1.Angle = P3.Angle + 225;
	P2.Angle = P3.Angle + 135;
	
	
}