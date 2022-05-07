#include "Ball.h"
#include "Renderer.h"
#include "Player.h"

#include <iostream>
using namespace std;

Ball::Ball(Renderer *Rend, Player* Player1) {
	this->Rend = Rend;
	this->Player1 = Player1;
	Velocity.x = 150;
	Velocity.y = 150;
	Position.x = 500;
	Position.y = 150;
	width = 10;
	height = 10;
}

void Ball::Update() {

	float DeltaTime = Rend->getDeltaTime();
	float XInc = DeltaTime * Velocity.x;
	float YInc = DeltaTime * Velocity.y;



	if (Position.x + XInc + width <= Rend->getWindowWidth() && Position.x + XInc >= 0)
		Position.x += XInc;
	else
		Velocity.x *= -1;


	if (Position.y + YInc + height <= Rend->getWindowHeight() && Position.y + YInc >= 0)
		Position.y += YInc;
	else
		Velocity.y *= -1;
	
	if (Position.x >= Player1->getXPosition() && Position.x + width <= Player1->getXPosition() + Player1->getWidth()) {
		if (Position.y + height >= Player1->getYPosition() && Position.y + height <= Player1->getYPosition() + Player1->getHeight()) {
			Velocity.x *= -1;
			Velocity.y *= -1;
		}

	}

	Rend->DrawRect(Position.x, Position.y, width, height, 255, 153, 204, 255);


	
}