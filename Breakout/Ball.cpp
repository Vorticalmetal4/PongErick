#include "Ball.h"
#include "CommonFiles/Renderer.h"
#include "Player.h"
#include "Brick.h"
#include "HUD.h"
#include "Inih/cpp/INIReader.h"

#include <ctime>

Ball::Ball(Renderer *_Rend, CollisionSystem* _CollisionDetector,Player* _Player1) 
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	Player1(_Player1),
	CollWPlayer(false),
	XInc(0),
	YInc(0),
	PlayerXPosition(0),
	DeltaTime(0)
{

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ball could not find ConFile");

	InitialVelocity = (float)ConFile.GetInteger("Ball", "InitialVelocity", -1);
	Velocity.x = InitialVelocity;
	Velocity.y = InitialVelocity;
	MaxVelocity = (float)ConFile.GetInteger("Ball", "MaxVelocity", 1);
	VelocityIncrease = ConFile.GetInteger("Ball", "VelocityIncrease", 1);
	InitialPosition.x = (float)ConFile.GetInteger("Ball", "InitialX", -1);
	InitialPosition.y = (float)ConFile.GetInteger("Ball", "InitialY", -1);

	Dimensions.Width = (float)ConFile.GetInteger("Ball", "Size", 1);
	Dimensions.Height = Dimensions.Width;
	CurrentPosition.x = InitialPosition.x;
	CurrentPosition.y = InitialPosition.y;

	srand((unsigned int)(time(NULL)));
	if ((rand() % (10 - 2 + 1) + 2) % 2 == 0)
		Velocity.x *= -1;
}

bool Ball::Update(bool Pause) 
{
	if (!Pause)
	{
		DeltaTime = Rend->getDeltaTime();
		XInc = DeltaTime * Velocity.x;
		YInc = DeltaTime * Velocity.y;

		if (CurrentPosition.x + XInc + Dimensions.Width <= Rend->getWindowWidth() && CurrentPosition.x + XInc >= 0)
			CurrentPosition.x += XInc;
		else
		{ //Collision with the walls
			Velocity.x *= -1;
			IncXVelocity();
			IncYVelocity();
			CollWPlayer = false;
		}


		if (CurrentPosition.y + YInc + Dimensions.Height <= Rend->getWindowHeight() && CurrentPosition.y + YInc >= 0) //Collition with the roof
			CurrentPosition.y += YInc;
		else
		{
			if (CurrentPosition.y + YInc + Dimensions.Height >= Rend->getWindowHeight())
			{ //The ball passed the player's line
				CurrentPosition.x = InitialPosition.x;
				CurrentPosition.y = InitialPosition.y;
				Velocity.x = InitialVelocity;
				Velocity.y = InitialVelocity;
				CollWPlayer = false;
				if ((rand() % (10 - 2 + 1) + 2) % 2 == 0)
					Velocity.x *= -1;
				return false;
			}

			else {
				Velocity.y *= -1;
				CollWPlayer = false;
			}
		}



		if (CurrentPosition.y > Rend->getWindowHeight() / 2)
		{ //Collision with the player only if the ball is on the player's side
			if (CollisionDetector->Square_Square(&CurrentPosition, Player1->getPosition(), &Dimensions, Player1->getDimensions()))
			{
				Velocity.y *= -1;
				IncXVelocity();
				IncYVelocity();
				CollWPlayer = true;

				if (CurrentPosition.x + Dimensions.Width / 2 >= PlayerXPosition + Player1->getWidth() / 2)
				{ //Chech the collision side
					if (Velocity.x < 0)
						Velocity.x *= -1;
				}
				else
				{
					if (Velocity.x > 0)
						Velocity.x *= -1;
				}
			}
		}
	}

	Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 255, 153, 204, 255);
	return true;
	
}

void Ball::IncXVelocity()
{
	if (Velocity.x > 0)
	{
		if (Velocity.x + VelocityIncrease <= MaxVelocity)
			Velocity.x += VelocityIncrease;
	}
	else
	{
		if (Velocity.x - VelocityIncrease >= MaxVelocity)
			Velocity.x -= VelocityIncrease;
	}
}

void Ball::IncYVelocity() 
{
	if (Velocity.y > 0) 
	{
		if (Velocity.y + VelocityIncrease <= MaxVelocity)
			Velocity.y += VelocityIncrease;
	}
	else
	{
		if (Velocity.y - VelocityIncrease >= MaxVelocity)
			Velocity.y -= VelocityIncrease;
	}

}