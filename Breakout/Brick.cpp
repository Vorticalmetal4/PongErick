#include "Brick.h"
#include "CommonFiles/Renderer.h"
#include "Ball.h"
#include "Inih/cpp/INIReader.h"
#include <cmath>

Brick::Brick(Renderer* _Rend, CollisionSystem* _CollisionDetector,int XPosition, int YPosition, float Separation)
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	Active(true),
	Traitor(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Brick");

	Dimensions.Width = (float)ConFile.GetInteger("Brick", "width", 0);
	Dimensions.Height = (float)ConFile.GetInteger("Brick", "height", 0);
	CurrentPosition.x = (float)ConFile.GetInteger("Brick", "InitialX", 0);
	CurrentPosition.y = (float)ConFile.GetInteger("Brick", "InitialY", 0);
	VerticalSeparation = (float)ConFile.GetInteger("Brick", "VerticalSeparation", 0);

	CurrentPosition.x += XPosition * Dimensions.Width + XPosition * Separation;
	CurrentPosition.y += YPosition * Dimensions.Height + YPosition * VerticalSeparation;
}

Brick::~Brick() 
{
	
}

void Brick::Draw(int Row) 
{
	switch (Row) 
	{
		case 0:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 255, 0, 0, 255); //Red
		break;

		case 1:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 255, 128, 0, 255); //Orange
		break;

		case 2:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 0, 255, 128, 255); //Light Green
		break;

		case 3:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 102, 178, 255, 255); //Light Blue
		break;

		case 4:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 0, 128, 255, 255); //Dark Blue
		break;

		default:
			Rend->DrawSimpleRect(&CurrentPosition, &Dimensions, 76, 0, 153, 255); //Dark Purple
		break;
	}
}


bool Brick::CheckCollition(Ball* Ball)
{
	if (CollisionDetector->Square_Square(&CurrentPosition, Ball->getPosition(), &Dimensions, Ball->getDimensions()))
	{
		Active = false;
		Ball->SetCollitionWPlayer();
		Ball->ChangeYDirection();
		Ball->IncXVelocity();
		Ball->IncYVelocity();
		if (Ball->getPosition()->x + Ball->getDimensions()->Width / 2 >= CurrentPosition.x + Dimensions.Width / 2) 
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

