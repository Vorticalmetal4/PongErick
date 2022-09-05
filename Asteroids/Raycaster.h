#pragma once

#include "CommonFiles/CollisionSystem.h"

class Raycaster
{
public: 
	Raycaster(void) = default;
	Raycaster(class Renderer* _Rend);
	~Raycaster();

	bool getActive() { return Active; }

	void setActive(bool _Active) { Active = _Active; }

	void Update(int Velocity, Position* ParentP);
	bool CheckCollision(float PlayerX, float PlayerY, float PlayerH);

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