#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include "Score.h"
#include <iostream>

using namespace std;

Ball::Ball(int x, int y, int xVelocity, int yVelocity, int Size) {
	xPosition = x;
	yPosition = y;
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
	this->Size = Size;
}

int Ball::getXPosition() { return xPosition; } // ESTILO: Este formato es mas comun en .h y no cpp

int Ball::getYPosition() { return yPosition; }

int Ball::getXVelocity() { return xVelocity; }

int Ball::getYVelocity() { return yVelocity; }

int Ball::getSize() { return Size; }

void Ball::GameStarted() {
	int na1 = 1 + rand() % (10 - 1);
	int na2 = 1 + rand() % (10 - 1);

	srand(time(NULL));

	if (na1 % 2 == 0)
		xVelocity *= -1;

	if (na2 % 2 == 0)
		yVelocity *= -1;
}

void Ball::setXVelocity() {

	if (xVelocity > 0)
		if (xVelocity <= 400)
			xVelocity += 20;
		else
			if (xVelocity >= -400)
				xVelocity -= 20;

	xVelocity *= -1;
}

void Ball::setYVelocity() {
	if (yVelocity > 0)
		if (yVelocity <= 400)
			yVelocity += 20;
		else
			if (yVelocity >= -400)
				yVelocity -= 20;

	yVelocity *= 1;
}

void Ball::Move(int xinc, int yinc) {
	xPosition += xinc;
	yPosition += yinc;
}

void Ball::WallCollition(int Height, int Width, Score* Sc) {
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
}