#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include "Inih/cpp/INIReader.h"
#include "CommonFiles/Renderer.h"


Ball::Ball(Renderer* _Rend)
	:DeltaTime(0),
	IncrementX(0),
	IncrementY(0),
	Rend(_Rend)
{

	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Ball could not find the ConFile");

	OwnDimensions.Width = OwnDimensions.Height = (float)ConFile.GetInteger("Ball", "Size", 0);
	FirstPoint.x = Rend->getHWindowWidth();
	FirstPoint.y = Rend->getHWindowHeight();
	InitialPoint = FirstPoint;
	Velocity.y = Velocity.x = ConFile.GetInteger("Ball", "Velocity", 0);
	VelocityIncrement = ConFile.GetInteger("Ball", "VelocityIncrement", 0);
	DecreasesNumber = ConFile.GetInteger("Ball", "DecreasesNumber", 0);

}

void Ball::Update()
{
	DeltaTime = Rend->getDeltaTime();
	IncrementX = DeltaTime * Velocity.x;
	IncrementY = DeltaTime * Velocity.y;

	if (FirstPoint.y + OwnDimensions.Height + IncrementY >= Rend->getWindowHeight() || FirstPoint.y + IncrementY < 0)
		Velocity.y *= -1;

	FirstPoint.x += IncrementX;
	FirstPoint.y += IncrementY;
	
	Rend->DrawSimpleRect(&FirstPoint, &OwnDimensions, 255, 255, 255, 255);
}

void Ball::CollisionWPaddle()
{
	Velocity.x = (Velocity.x > 0) ? Velocity.x + VelocityIncrement : Velocity.x - VelocityIncrement;
	Velocity.x *= -1;
}

void Ball::Reset()
{
	Velocity.x = (Velocity.x > 0) ? Velocity.x - VelocityIncrement * DecreasesNumber : Velocity.x + VelocityIncrement * DecreasesNumber;
	Velocity.y = (Velocity.y > 0) ? Velocity.y - VelocityIncrement * DecreasesNumber : Velocity.y + VelocityIncrement * DecreasesNumber;
	FirstPoint = InitialPoint;
}