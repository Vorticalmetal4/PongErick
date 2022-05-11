#include "Brick.h"
#include "Renderer.h"
#include "Ball.h"
#include <cmath>

Brick::Brick(){
	width = 97;
	height = 20;
	Position.x = 5;
	Position.y = 100;
}

void Brick::setData(Renderer* Rend, int XPosition, int YPosition, float Separation) {
	this->Rend = Rend;
	Position.x += XPosition * width + XPosition * Separation;
	Position.y += YPosition * height + YPosition * Separation;
}

void Brick::Draw(int Row) {
	switch (Row) {
		case 0:
			Rend->DrawRect(Position.x, Position.y, width, height, 255, 0, 0, 255); //Red
		break;

		case 1:
			Rend->DrawRect(Position.x, Position.y, width, height, 255, 128, 0, 255); //Orange
		break;

		case 2:
			Rend->DrawRect(Position.x, Position.y, width, height, 0, 255, 128, 255); //Light Green
		break;

		case 3:
			Rend->DrawRect(Position.x, Position.y, width, height, 102, 178, 255, 255); //Light Blue
		break;

		case 4:
			Rend->DrawRect(Position.x, Position.y, width, height, 0, 128, 255, 255); //Dark Blue
		break;

		case 5:
			Rend->DrawRect(Position.x, Position.y, width, height, 76, 0, 153, 255); //Dark Purple
		break;
	}
}

void Brick::CheckCollition(Ball* Ball) {
	if (Ball->getXPosition() >= Position.x && Ball->getXPosition() + Ball->getWidth() <= Position.x + width) {
		if (Ball->getYPosition() + Ball->getHeight() >= Position.y && Ball->getYPosition() <= Position.y + height) {
			Ball->setXVelocity(-1);
			Ball->setYVelocity(-1);
		}
	}
}