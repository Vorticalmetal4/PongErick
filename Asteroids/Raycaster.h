#pragma once

#include "Renderer.h"

class Raycaster
{
public: 
	Raycaster(Renderer* _Rend);
	~Raycaster();

	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void Update(int Velocity, Position* EnemyP);
	bool CheckCollision(double PlayerX, double PlayerY, double PlayerH);

private:
	Renderer* Rend;
	bool Active;
	Position P1;
	Position P2;
	Position Center;
	float D;
	float DeltaTime;
	float m;
};