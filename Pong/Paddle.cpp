#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "SDL2/include/SDL.h"
#include "Paddle.h"
#include "Ball.h"

#include <iostream>

Paddle::Paddle(Renderer* _Rend, CollisionSystem* _CollisionDetector, Ball* _GameBall, bool _isPlayer1)
	:Rend(_Rend),
	CollisionDetector(_CollisionDetector),
	GameBall(_GameBall),
	DeltaTime(0),
	Increment(0),
	Score(0),
	isPlayer1(_isPlayer1),
	OtherPaddle(nullptr)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Paddle could not find the ConFile");

	Velocity = ConFile.GetInteger("Paddle", "Velocity", 0);
	OwnDimensions.Width = ConFile.GetInteger("Paddle", "Thickness", 0);
	OwnDimensions.Height = OwnDimensions.Width * 4;
	GoalDistance = ConFile.GetInteger("Paddle", "GoalDistance", 50);

	if (isPlayer1)
	{
		ScorePosition.x = (float)ConFile.GetInteger("HUD", "Player1ScoreXPosition", 0);
		FirstPoint.x = (float)ConFile.GetInteger("Paddle", "Player1XPosition", 0);
	}
	else
	{
		ScorePosition.x = (float)ConFile.GetInteger("HUD", "Player2ScoreXPosition", 0);
		FirstPoint.x = (float)ConFile.GetInteger("Paddle", "Player2XPosition", 0);
	}

	ScorePosition.y = (float)ConFile.GetInteger("HUD", "ScoreYPosition", 0);
	FirstPoint.y = (float)ConFile.GetInteger("Paddle", "InitialYPosition", 0);
	
	ScoreDimensions.Width = (float)ConFile.GetInteger("HUD", "ScoreWidth", 0);
	ScoreDimensions.Height = (float)ConFile.GetInteger("HUD", "ScoreHeight", 0);

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
	
	if (CollisionDetector->Square_Square(&FirstPoint, GameBall->getPosition(), &OwnDimensions, GameBall->getDimensions()))
		GameBall->CollisionWPaddle();
	else
	{
		if (isPlayer1)
		{
			if (GameBall->getPosition()->x < FirstPoint.x - GoalDistance)
			{
				OtherPaddle->IncreaseScore();
				GameBall->Reset();
			}
		}
		else
		{
			if (GameBall->getPosition()->x > FirstPoint.x + OwnDimensions.Width + GoalDistance)
			{
				OtherPaddle->IncreaseScore();
				GameBall->Reset();
			}
		}
	}

	PrintScore();
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

void Paddle::PrintScore()
{
	ScoreText = to_string(Score);
	ScoreText.copy(NText, ScoreText.size() + 1);
	NText[ScoreText.size() + 1] = '\0';
	Rend->Write(NText, ScoreDimensions.Width, ScoreDimensions.Height, ScorePosition.x, ScorePosition.y);
}