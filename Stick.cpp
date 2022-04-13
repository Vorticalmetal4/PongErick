#include "Stick.h"
#include "Ball.h"

Stick::Stick(int x, int y, int height, int Velocity, int Width) {
	xPosition = x;
	yPosition = y;
	this->height = height;
	this->Velocity = Velocity;
	this->Width = Width;

}

int Stick::getYPosition() { return yPosition; }

int Stick::getXPosition() { return xPosition; }

int Stick::getVelocity() { return Velocity; }

int Stick::getHeight() { return height; }

void Stick::MoveYPosition(int yInc) { yPosition += yInc; }

bool Stick::CheckBorders(int yInc, int top, int down) {
	if (yPosition + yInc >= top && (yPosition + height + yInc) <= down)
		return true;
	else
		return false;

}


bool Stick::CollitionWBall(Ball* GameBall, int Side) {


	if (Side == 1) {
		if (GameBall->getXPosition() >= xPosition && GameBall->getXPosition() <= xPosition + Width) {
			if (GameBall->getYPosition() <= yPosition + height && GameBall->getYPosition() >= yPosition) {
				GameBall->setXVelocity();
				GameBall->setYVelocity();
				return true;
			}
		}
	}
	else {
		if (GameBall->getXPosition() + GameBall->getSize() >= xPosition && GameBall->getXPosition() + GameBall->getSize() <= xPosition + Width) {
			if (GameBall->getYPosition() <= yPosition + height && GameBall->getYPosition() >= yPosition) {
				GameBall->setXVelocity();
				GameBall->setYVelocity();
				return true;
			}
		}
	}

	return false;

}