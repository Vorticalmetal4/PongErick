#pragma once
#include "CommonFiles/CollisionSystem.h"


class Renderer;
class Ball;

class Paddle {
public:
	Paddle(Renderer* _Rend, Ball* _GameBall, bool _isPlayer1);
	void Update();

private:
	Renderer* Rend;
	Ball* GameBall;
	Position FirstPoint;
	Dimension OwnDimensions;
	const Uint8* StateP;

	int Velocity;

	float DeltaTime;
	float Increment;

	bool isPlayer1;

	bool CheckInput(bool isGoingUp);
};
