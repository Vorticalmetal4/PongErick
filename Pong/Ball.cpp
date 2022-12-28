#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include "Inih/cpp/INIReader.h"
#include "CommonFiles/Renderer.h"
#include "Score.h"


Ball::Ball(Renderer* _Rend)
	:DeltaTime(0),
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

	if (FirstPoint.x + IncrementX >= Rend->getWindowWidth() || FirstPoint.x + IncrementX < 0)
	{
		Velocity.x = (Velocity.x > 0) ? Velocity.x - VelocityIncrement * DecreasesNumber : Velocity.x + VelocityIncrement * DecreasesNumber;
		Velocity.y = (Velocity.y > 0) ? Velocity.y - VelocityIncrement * DecreasesNumber : Velocity.y + VelocityIncrement * DecreasesNumber;
		FirstPoint = InitialPoint;
	}

	if (FirstPoint.y + OwnDimensions.Height + IncrementY >= Rend->getWindowHeight() || FirstPoint.y + IncrementY < 0)
		Velocity.y *= -1;

	FirstPoint.x += IncrementX;
	FirstPoint.y += IncrementY;
	
	Rend->DrawSimpleRect(&FirstPoint, &OwnDimensions, 255, 255, 255, 255);
}

/*void Ball::WallCollition(int Height, int Width, Score* Sc) {
	if (xPosition >= Width || xPosition <= 0) {
		xVelocity *= -1;
		if (xPosition > Width / 2)
			Sc->Player1Goal();
		else
			Sc->Player2Goal();
		xPosition = static_cast<int>(Width / 2); // CPP: No casting on update loops, NO!
		yPosition = static_cast<int>(Height / 2);

		if (xVelocity >= 0) {
			if (xVelocity > 200)
				xVelocity -= 50;
			else
				xVelocity = 150;
		}
		else {
			if (xVelocity < -200)
				xVelocity += 50;
			else
				xVelocity = -150;
		}

		if (yVelocity >= 0) {
			if (yVelocity > 200)
				yVelocity -= 50;
			else
				yVelocity = 150;
		}
		else {
			if (yVelocity < -200)
				yVelocity += 50;
			else
				yVelocity = -150;
		}


	}
	else if (yPosition + Size >= Height || yPosition <= 0)
		yVelocity *= -1;
}*/