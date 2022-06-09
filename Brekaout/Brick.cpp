#include "Brick.h"
#include "Renderer.h"
#include "Ball.h"
#include <cmath>

Brick::Brick()
{
	Rend = nullptr;
	width = 97;
	height = 20;
	Position.x = 5;
	Position.y = 100;
	Active = true;
}

Brick::~Brick() 
{
	
}

void Brick::setData(Renderer* _Rend, int XPosition, int YPosition, float Separation)
{
	Rend = _Rend;
	Position.x += XPosition * width + XPosition * Separation;
	Position.y += YPosition * height + YPosition * Separation;
}

void Brick::Draw(int Row) 
{
	switch (Row) 
	{
		case 0:
			Rend->DrawRect(Position.x, Position.y, width, height, 255, 0, 0, 255); //Red
		break;

		case 1:
			Rend->DrawRect(Position.x, Position.y, width, height, 255, 128, 0, 255); //Orange
		break;

		case 2:
			Rend->DrawRect(Position.x, Position.y, width, height, 0, 255, 128, 255); //Light Green
		break;

		case 3:
			Rend->DrawRect(Position.x, Position.y, width, height, 102, 178, 255, 255); //Light Blue
		break;

		case 4:
			Rend->DrawRect(Position.x, Position.y, width, height, 0, 128, 255, 255); //Dark Blue
		break;

		case 5:
			Rend->DrawRect(Position.x, Position.y, width, height, 76, 0, 153, 255); //Dark Purple
		break;
	}
}


bool Brick::CheckCollition(Ball* Ball)
{
	if (Ball->getXPosition() >= Position.x && Ball->getXPosition() + Ball->getWidth() <= Position.x + width)
	{
		if (Ball->getYPosition() >= Position.y && Ball->getYPosition() <= Position.y + height)
		{
			Active = false;
			Ball->SetCollitionWPlayer();
		}
		else if (Ball->getYPosition() + Ball->getHeight() >= Position.y && Ball->getYPosition() + Ball->getHeight() <= Position.y + height) {
			Active = false;
			Ball->SetCollitionWPlayer();
		}
		else
			return false;

		Ball->ChangeYDirection();
		Ball->IncXVelocity();
		Ball->IncYVelocity();
		if (Ball->getXPosition() + Ball->getWidth() / 2 >= Position.x + width / 2) 
		{ //If the ball collide with the rigth part
			if (Ball->getXVelocity() < 0) 	//And Velocity < 0
				Ball->ChangeXDirection();  //Change the direction
		}
		else 
		{
			if (Ball->getXVelocity() > 0) 
				Ball->ChangeXDirection();
		}

		return true;
	}
	return false;

}

