#include "Renderer.h"
#include "Player.h"
#include "../SDL2/include/SDL.h"

const Uint8* state = SDL_GetKeyboardState(NULL);

Player::Player(Renderer* Rend) {
	this -> Rend = Rend;
	PlayerVelocity = 200;
	Position.x = 500;
	Position.y = 650;
	width = 80;
	height = 20;

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

	Rend->DrawRect(Position.x, Position.y, width, height);


}

