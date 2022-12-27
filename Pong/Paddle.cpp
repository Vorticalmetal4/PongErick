#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(int x, int y, int _Height, int _Velocity, int _Width) {
	xPosition = x;
	yPosition = y;
	Height = _Height;
	Velocity = _Velocity;
	Width = _Width;

}


void Paddle::Move(int yInc) { yPosition += yInc; }

bool Paddle::CheckBorders(int yInc, int top, int down) {
	if (yPosition + yInc >= top && (yPosition + Height + yInc) <= down)
		return true;
	else
		return false;
}


bool Paddle::CollitionWBall(Ball* GameBall, int Side) {


	if (Side == 1) {
		if (GameBall->getXPosition() >= xPosition && GameBall->getXPosition() <= xPosition + Width) {
			if (GameBall->getYPosition() <= yPosition + Height && GameBall->getYPosition() >= yPosition) {
				GameBall->setXVelocity();
				GameBall->setYVelocity();
				return true;
			}
		}
	}
	else {
		if (GameBall->getXPosition() + GameBall->getSize() >= xPosition && GameBall->getXPosition() + GameBall->getSize() <= xPosition + Width) {
			if (GameBall->getYPosition() <= yPosition + Height && GameBall->getYPosition() >= yPosition) {
				GameBall->setXVelocity();
				GameBall->setYVelocity();
				return true;
			}
		}
	}

	return false;

}
