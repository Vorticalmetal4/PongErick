#pragma once
#include "CommonFiles/CollisionSystem.h"

class Brick 
{
public:
	Brick(class Renderer* _Rend, int XPosition, int YPosition, float Separation);
	~Brick();
	void Draw(int raw);

	int getXPosition() { return ActualPosition.x; }
	int getYPosition() { return ActualPosition.y; }
	int getWidth() { return Dimensions.Width; }
	int getHeight() { return Dimensions.Height; }
	bool getActive() { return Active; }
	bool getTraitor() { return Traitor; }
	void setActive(bool Change) { Active = Change; }
	void setTraitor(bool Change) { Traitor = Change; }
	bool CheckCollition(class Ball* Ball);
	void setYPosition(int Y) {ActualPosition.y = Y; }

private:
	Position ActualPosition;
	Dimension Dimensions;
	Renderer* Rend;
	bool Active;
	bool Traitor;
	float VerticalSeparation;
	
};