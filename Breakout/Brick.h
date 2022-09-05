#pragma once
#include "CommonFiles/CollisionSystem.h"

class Brick 
{
public:
	Brick(class Renderer* _Rend, int XPosition, int YPosition, float Separation);
	~Brick();
	void Draw(int raw);

	float getXPosition() { return ActualPosition.x; }
	float getYPosition() { return ActualPosition.y; }
	float getWidth() { return Dimensions.Width; }
	float getHeight() { return Dimensions.Height; }
	bool getActive() { return Active; }
	bool getTraitor() { return Traitor; }
	void setActive(bool Change) { Active = Change; }
	void setTraitor(bool Change) { Traitor = Change; }
	bool CheckCollition(class Ball* Ball);
	void setYPosition(float Y) {ActualPosition.y = Y; }

private:
	Position ActualPosition;
	Dimension Dimensions;
	Renderer* Rend;
	bool Active;
	bool Traitor;
	float VerticalSeparation;
	
};