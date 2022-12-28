#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "SDL2/include/SDL.h"
#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(Renderer* _Rend, Ball* _GameBall, bool _isPlayer1)
	:Rend(_Rend),
	GameBall(_GameBall),
	DeltaTime(0),
	isPlayer1(_isPlayer1)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Paddle could not find the ConFile");

	Velocity = ConFile.GetInteger("Paddle", "Velocity", 0);
	OwnDimensions.Width = ConFile.GetInteger("Paddle", "Thickness", 0);
	OwnDimensions.Height = OwnDimensions.Width * 4;

	if (isPlayer1)
		FirstPoint.x = (float)ConFile.GetInteger("Paddle", "Player1XPosition", 0);
	else
		FirstPoint.x = (float)ConFile.GetInteger("Paddle", "Player2XPosition", 0);

	FirstPoint.y = (float)ConFile.GetInteger("Paddle", "InitialYPosition", 0);

	StateP = Rend->getState();

}


void Paddle::Update()
{
	DeltaTime = Rend->getDeltaTime();
	Increment = Velocity * DeltaTime;

	if (CheckInput(true))
		FirstPoint.y = (FirstPoint.y - Increment > 0) ? FirstPoint.y - Increment : FirstPoint.y;
	else if(CheckInput(false))
		FirstPoint.y = (FirstPoint.y + Increment + OwnDimensions.Height < Rend->getWindowHeight()) ? FirstPoint.y + Increment : FirstPoint.y;

	Rend->DrawSimpleRect(&FirstPoint, &OwnDimensions, 255, 255, 255, 255);
}

bool Paddle::CheckInput(bool isGoingUp)
{
	if (isGoingUp)
	{
		if (isPlayer1)
		{
			if (StateP[SDL_SCANCODE_W])
				return true;
		}
		else
			if (StateP[SDL_SCANCODE_UP])
				return true;
	}
	else
	{
		if (isPlayer1)
		{
			if (StateP[SDL_SCANCODE_S])
				return true;
		}
		else
			if (StateP[SDL_SCANCODE_DOWN])
				return true;
	}

	return false;
}
