#pragma once
#include "CommonFiles/CollisionSystem.h"

class Brick 
{
public:
	Brick(class Renderer* _Rend,  CollisionSystem* _CollisionDetector,int XPosition, int YPosition, float Separation);
	~Brick();
	void Draw(int raw);

	Position* getPosition() { return &CurrentPosition; };
	Dimension* getDimensions() { return &Dimensions; }
	float getWidth() { return Dimensions.Width; }
	float getHeight() { return Dimensions.Height; }
	bool getActive() { return Active; }
	bool getTraitor() { return Traitor; }
	void setActive(bool Change) { Active = Change; }
	void setTraitor(bool Change) { Traitor = Change; }
	bool CheckCollition(class Ball* Ball);
	void setYPosition(float Y) {CurrentPosition.y = Y; }

private:
	Position CurrentPosition;
	CollisionSystem* CollisionDetector;
	Dimension Dimensions;
	Renderer* Rend;
	bool Active;
	bool Traitor;
	float VerticalSeparation;
	
};