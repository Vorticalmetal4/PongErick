#pragma once
#include "CommonFiles/CollisionSystem.h"


class Renderer;
class Ball;

class Paddle {
public:
	Paddle(Renderer* _Rend, CollisionSystem* _CollisionDetector,Ball* _GameBall, bool _isPlayer1);
	void setOtherPaddle(Paddle* _OtherPaddle) { OtherPaddle = _OtherPaddle; };
	void IncreaseScore() { Score++; }
	void Update();

private:
	Renderer* Rend;
	CollisionSystem* CollisionDetector;
	Ball* GameBall;
	Position FirstPoint;
	Position ScorePosition;
	Dimension OwnDimensions;
	Dimension ScoreDimensions;
	Paddle* OtherPaddle;

	const Uint8* StateP;

	int Velocity;
	int GoalDistance;
	

	long Score;

	float DeltaTime;
	float Increment;

	bool isPlayer1;

	string ScoreText;

	char NText[3];

	bool CheckInput(bool isGoingUp);
	void PrintScore();
};
