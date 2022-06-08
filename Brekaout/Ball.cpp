#include "Ball.h"
#include "Renderer.h"
#include "Player.h"
#include "Brick.h"
#include "HUD.h"
#include "../Inih/cpp/INIReader.h"
#include <ctime>

Ball::Ball(Renderer *_Rend, Player* _Player1) 
	:Rend(_Rend),
	Player1(_Player1)
{



	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ball");

	InitialVelocity = ConFile.GetInteger("Ball", "InitialVelocity", -1);
	Velocity.x = InitialVelocity;
	Velocity.y = InitialVelocity;
	MaxVelocity = ConFile.GetInteger("Ball", "MaxVelocity", 1);
	VelocityIncrease = ConFile.GetInteger("Ball", "VelocityIncrease", 1);
	InitialPosition.x = ConFile.GetInteger("Ball", "InitialX", -1);
	InitialPosition.y = ConFile.GetInteger("Ball", "InitialY", -1);
	width = ConFile.GetInteger("Ball", "Size", 1);
	height = width;
	Position.x = InitialPosition.x;
	Position.y = InitialPosition.y;

	srand(time(NULL));
	if ((rand() % (10 - 2 + 1) + 2) % 2 == 0)
		Velocity.x *= -1;
}

bool Ball::Update() 
{

	float DeltaTime = Rend->getDeltaTime();
	float XInc = DeltaTime * Velocity.x;
	float YInc = DeltaTime * Velocity.y;
	int PlayerXPosition = Player1->getXPosition();



	if (Position.x + XInc + width <= Rend->getWindowWidth() && Position.x + XInc >= 0)
		Position.x += XInc;
	else
	{ //Collision with the walls
		Velocity.x *= -1;
		IncXVelocity();
		IncYVelocity();
	}


	if (Position.y + YInc + height <= Rend->getWindowHeight() && Position.y + YInc >= 0) //Collition with the roof
		Position.y += YInc;
	else
	{
		if (Position.y + YInc + height >= Rend->getWindowHeight()) 
		{ //The ball passed the player's line
			Position.x = InitialPosition.x;
			Position.y = InitialPosition.y;
			Velocity.x = InitialVelocity;
			Velocity.y = InitialVelocity;
			if ((rand() % (10 - 2 + 1) + 2) % 2 == 0)
				Velocity.x *= -1;
			return false;
		}

		else
			Velocity.y *= -1;
	}

		

	if (Position.y > Rend->getWindowHeight() / 2)
	{ //Collision with the player only if the ball is on the player's side
		if (Position.x >= PlayerXPosition && Position.x + width <= PlayerXPosition + Player1->getWidth())
		{
			if (Position.y + height >= Player1->getYPosition() && Position.y + height <= Player1->getYPosition() + Player1->getHeight())
			{
				Velocity.y *= -1;
				IncXVelocity();
				IncYVelocity();

				if (Position.x + width / 2 >= PlayerXPosition + Player1->getWidth() / 2) 
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

	Rend->DrawRect(Position.x, Position.y, width, height, 255, 153, 204, 255);
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