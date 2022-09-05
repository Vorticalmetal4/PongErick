#include "Brick.h"
#include "CommonFiles/Renderer.h"
#include "Ball.h"
#include "Inih/cpp/INIReader.h"
#include <cmath>

Brick::Brick(Renderer* _Rend, int XPosition, int YPosition, float Separation)
	:Rend(_Rend),
	Active(true),
	Traitor(false)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Brick");

	Dimensions.Width = (float)ConFile.GetInteger("Brick", "width", 0);
	Dimensions.Height = (float)ConFile.GetInteger("Brick", "height", 0);
	ActualPosition.x = (float)ConFile.GetInteger("Brick", "InitialX", 0);
	ActualPosition.y = (float)ConFile.GetInteger("Brick", "InitialY", 0);
	VerticalSeparation = ConFile.GetReal("Brick", "VerticalSeparation", 0);

	ActualPosition.x += XPosition * Dimensions.Width + XPosition * Separation;
	ActualPosition.y += YPosition * Dimensions.Height + YPosition * VerticalSeparation;
}

Brick::~Brick() 
{
	
}

void Brick::Draw(int Row) 
{
	switch (Row) 
	{
		case 0:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 255, 0, 0, 255); //Red
		break;

		case 1:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 255, 128, 0, 255); //Orange
		break;

		case 2:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 0, 255, 128, 255); //Light Green
		break;

		case 3:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 102, 178, 255, 255); //Light Blue
		break;

		case 4:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 0, 128, 255, 255); //Dark Blue
		break;

		default:
			Rend->DrawSimpleRect(&ActualPosition, &Dimensions, 76, 0, 153, 255); //Dark Purple
		break;
	}
}


bool Brick::CheckCollition(Ball* Ball)
{
	if (Ball->getXPosition() >= ActualPosition.x && Ball->getXPosition() + Ball->getWidth() <= ActualPosition.x + Dimensions.Width)
	{
		if (Ball->getYPosition() >= ActualPosition.y && Ball->getYPosition() <= ActualPosition.y + Dimensions.Height)
		{
			Active = false;
			Ball->SetCollitionWPlayer();
		}
		else if (Ball->getYPosition() + Ball->getHeight() >= ActualPosition.y && Ball->getYPosition() + Ball->getHeight() <= ActualPosition.y + Dimensions.Height) {
			Active = false;
			Ball->SetCollitionWPlayer();
		}
		else
			return false;

		Ball->ChangeYDirection();
		Ball->IncXVelocity();
		Ball->IncYVelocity();
		if (Ball->getXPosition() + Ball->getWidth() / 2 >= ActualPosition.x + Dimensions.Width / 2) 
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

