#include "Renderer.h"
#include "Player.h"
#include "../SDL2/include/SDL.h"

#include <iostream>
#include <string>
#include "../Inih/cpp/INIReader.h"

using namespace std;

const Uint8* state = SDL_GetKeyboardState(NULL);

Player::Player(Renderer* Rend) {

	//INIReader ConFile("D:/Erick/Documentos/Curso Cremaster/Proyectos Erick/Brekaout/InitialData.ini");
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		cout << "Couldn't find the Configuration File" << endl;

	this -> Rend = Rend;
	PlayerVelocity = ConFile.GetInteger("Player", "PlayerVelocity", -1);
	Position.x = ConFile.GetInteger("Player", "PositionX", 1);
	Position.y = ConFile.GetInteger("Player", "PositionY", 1);
	width = ConFile.GetInteger("Player", "Width", 80);
	height = ConFile.GetInteger("Player", "Height", 20);


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


