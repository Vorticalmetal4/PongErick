#include "EnemyShip.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Raycaster.h"

#include <cmath>

const float Pi = (float)3.141592;
const float Rad = Pi / 180;


EnemyShip::EnemyShip(Renderer* _Rend)
	:Rend(_Rend),
	Active(false),
	Ray(_Rend),
	wasPlayerUp(false),
	wasPlayerLeft(false),
	ChangeDirection(false),
	TurnLeft(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("EnemyShip");

	OwnDimensions.Width = ConFile.GetInteger("EnemyShip", "Width", 0);
	OwnDimensions.Height = ConFile.GetInteger("EnemyShip", "Height", 0);
	Velocity = ConFile.GetInteger("EnemyShip", "Velocity", 0);
	HWidth = OwnDimensions.Width / 2.0f;
	HHeight = OwnDimensions.Height / 2.0f;
	OwnDimensions.Hypotenuse = sqrtf(powf(HHeight, 2) + powf(HWidth, 2));

	setNewData(true, false);
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::Update(Position* PlayerCenter, float PlayerHypotenuse, bool Pause)
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();

		if (!Ray.CheckCollision(PlayerCenter->x, PlayerCenter->y, PlayerHypotenuse))
		{

			if ( ((PlayerCenter->y < Center.y && wasPlayerUp) || (PlayerCenter->y > Center.y && !wasPlayerUp)) && ((PlayerCenter->x < Center.x && wasPlayerLeft) || (PlayerCenter->x > Center.x && !wasPlayerLeft)))
				ChangeDirection = false;
			else
				ChangeDirection = true;

			if(ChangeDirection)
			{
				if (PlayerCenter->y <= Center.y)
					wasPlayerUp = true;
				else
					wasPlayerUp = false;

				if (PlayerCenter->x <= Center.x)
					wasPlayerLeft = true;
				else
					wasPlayerLeft = false;

				if ((wasPlayerUp && P3.x >= Center.x) || (!wasPlayerUp && P3.x <= Center.x))
					TurnLeft = true;
				else
					TurnLeft = false;

				ChangeDirection = false;
			}

			if (TurnLeft)
			{
				P1.Angle++;
				P2.Angle++;
				P3.Angle++;
				Center.Angle++;
			}
			else
			{
				P1.Angle--;
				P2.Angle--;
				P3.Angle--;
				Center.Angle--;
			}

		}
		else
		{
			Center.x += cosf(Center.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(Center.Rotation) * Velocity * DeltaTime;
		}

		Ray.Update(Velocity, &P3);

		P1.Rotation = (P1.Angle * Rad);
		P2.Rotation = (P2.Angle * Rad);
		Center.Rotation = P3.Rotation = (Center.Angle * Rad);

		P3.x = Center.x + cosf(P3.Rotation) * OwnDimensions.Hypotenuse;
		P3.y = Center.y - sinf(P3.Rotation) * OwnDimensions.Hypotenuse;
		P2.x = Center.x + cosf(P2.Rotation) * OwnDimensions.Hypotenuse;
		P2.y = Center.y - sinf(P2.Rotation) * OwnDimensions.Hypotenuse;
		P1.x = Center.x + cosf(P1.Rotation) * OwnDimensions.Hypotenuse;
		P1.y = Center.y - sinf(P1.Rotation) * OwnDimensions.Hypotenuse;

		if (Center.x > Rend->getWindowWidth())
			Center.x = 0;
		else if (Center.x < 0)
			Center.x = (float)Rend->getWindowWidth();

		if (Center.y > Rend->getWindowHeight())
			Center.y = 0;
		else if (Center.y < 0)
			Center.y = (float)Rend->getWindowHeight();
	}

	Rend->DrawTriangle(&P1, &P2, &P3, 0, 0, 0, 255);
}

void EnemyShip::setNewData(bool Left, bool _Active)
{
	Active = _Active;
	Ray.setActive(true);
	wasPlayerUp = false;
	wasPlayerLeft = false;

	P3.y = Center.y = Rend->getWindowHeight() / 2.0f;

	if (Left)
	{
		P1.x = P2.x = (float) - OwnDimensions.Height;
		P3.x = 0;
		P2.y = P3.y + HWidth;
		P1.y = P3.y - HWidth;
		Center.x = P3.x - HHeight;
	}
	else
	{
		P1.x = P2.x = (float)Rend->getWindowWidth() + OwnDimensions.Height;
		P3.x = (float)Rend->getWindowWidth();
		P2.y = P3.y - HWidth;
		P1.y = P3.y + HWidth;
		Center.x = P3.x + HHeight;
	}

	P3.Angle = Center.Angle = 0;
	P1.Angle = P3.Angle + 225;
	P2.Angle = P3.Angle + 135;
	
	
}