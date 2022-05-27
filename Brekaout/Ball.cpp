#include "Ball.h"
#include "Renderer.h"
#include "Player.h"
#include "Brick.h"
#include "HUD.h"
#include "../Inih/cpp/INIReader.h"
#include <iostream>

using namespace std;

Ball::Ball(Renderer *Rend, Player* Player1, HUD* Hud) {
	this->Rend = Rend;
	this->Player1 = Player1;
	this->Hud = Hud;


	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Ball: Couldn't find the Configuration File" << endl;

	Velocity.x = ConFile.GetInteger("Ball", "InitialVelocity", -1);
	Velocity.y = ConFile.GetInteger("Ball", "InitialVelocity", -1);
	InitialPosition.x = ConFile.GetInteger("Ball", "InitialX", -1);
	InitialPosition.y = ConFile.GetInteger("Ball", "InitialY", -1);
	width = ConFile.GetInteger("Ball", "Size", 1);
	height = width;
	Position.x = InitialPosition.x;
	Position.y = InitialPosition.y;
}

void Ball::Update() {

	float DeltaTime = Rend->getDeltaTime();
	float XInc = DeltaTime * Velocity.x;
	float YInc = DeltaTime * Velocity.y;
	int PlayerXPosition = Player1->getXPosition();



	if (Position.x + XInc + width <= Rend->getWindowWidth() && Position.x + XInc >= 0)
		Position.x += XInc;
	else
		Velocity.x *= -1;


	if (Position.y + YInc + height <= Rend->getWindowHeight() && Position.y + YInc >= 0)
		Position.y += YInc;
	else {
		if (Position.y + YInc + height >= Rend->getWindowHeight()) {
			Hud->LoseALife();
			Position.x = InitialPosition.x;
			Position.y = InitialPosition.y;
		}

		else
			Velocity.y *= -1;
	}

		

	if (Position.y > Rend->getWindowHeight() / 2) {
		if (Position.x >= PlayerXPosition && Position.x + width <= PlayerXPosition + Player1->getWidth()) {
			if (Position.y + height >= Player1->getYPosition() && Position.y + height <= Player1->getYPosition() + Player1->getHeight()) {
				Velocity.y *= -1;
				if (Position.x + width / 2 >= PlayerXPosition + Player1->getWidth() / 2) {
					if (Velocity.x < 0)
						Velocity.x *= -1;
				}
				else {
					if (Velocity.x > 0)
						Velocity.x *= -1;
				}
			}

		}
	}


	Rend->DrawRect(Position.x, Position.y, width, height, 255, 153, 204, 255);


	
}