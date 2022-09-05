#pragma once
#include "CommonFiles/CollisionSystem.h"

struct Color
{
	int r;
	int g; 
	int b;
	int alpha;
};

class Wall
{
public:
	Wall(void) = default;
	Wall(class Renderer* _Rend, float _x, float _y, float _Width, float _Height);
	Wall(class Renderer* _Rend, float _x, float _y, float _Width, float _Height, int r, int g, int b, int alpha);
	~Wall();

	Position* getPosition() { return &P1; };
	Dimension* getDimension() { return &OwnDimensions; }

	void Draw();

private:
	Renderer* Rend;
	Dimension OwnDimensions;
	Position P1;
	Color WallColor;

};