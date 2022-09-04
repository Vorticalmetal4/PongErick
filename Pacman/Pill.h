#pragma once

#include "CollisionSystem.h"

class Pill {
public:
	Pill(void) = default;
	Pill(class Renderer* _Rend, float x, float y);
	~Pill();

	void Update();

private:
	Position Center;
	Renderer* Rend;

	float Radius;


};