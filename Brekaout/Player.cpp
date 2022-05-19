#include "Renderer.h"
#include "Player.h"
#include "../SDL2/include/SDL.h"

#include <iostream>
#include "../Inih/cpp/INIReader.h"


using namespace std;

const Uint8* state = SDL_GetKeyboardState(NULL);

Player::Player(Renderer* Rend) {

	INIReader ConFile("./InitialData.ini");

	if (ConFile.ParseError() < 0) 
		cout << "Couldn't find InitialData.ini" << endl;


	this -> Rend = Rend;
	PlayerVelocity = ConFile.GetInteger("Player", "PlayerVelocity", -1);
	Position.x = 500;
	Position.y = 650;
	width = 80;
	height = 20;


	cout << PlayerVelocity;
}

void Player::Update() {
	
	if (Rend->getmIsRunning()) {
		if (state[SDL_SCANCODE_D])
			if(Position.x + (PlayerVelocity * Rend->getDeltaTime() + width) <= Rend -> getWindowWidth())
				Position.x += PlayerVelocity * Rend->getDeltaTime();
		if (state[SDL_SCANCODE_A])
			if(Position.x - PlayerVelocity * Rend->getDeltaTime() >= 0)
				Position.x -= PlayerVelocity * Rend->getDeltaTime();
	}

	Rend->DrawRect(Position.x, Position.y, width, height, 178, 102, 255, 255);

}


