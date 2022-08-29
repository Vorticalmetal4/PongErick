#pragma once
#include "CollisionSystem.h"

class Wall
{
public:
	Wall(void) = default;
	Wall(class Renderer* _Rend, float _x, float _y, float _Width, float _Height);
	~Wall();

	Position* getPosition() { return &P1; };
	Dimension* getDimension() { return &OwnDimensions; }

	void Draw();

private:
	Renderer* Rend;
	Dimension OwnDimensions;
	Position P1;

};