#pragma once
#include "CollisionSystem.h"

class Triangle 
{
public: 
	Triangle();
	~Triangle();

	void setPointData(float x, float y, int Angle, int Position);
	void setDimensions(float Width, float Height);

	Position* getFirstPoint() { return &P1; }
	Position* getSecondPoint() { return &P2; }
	Position* getThirdPoint() { return &P3; }
	Position* getCenter() { return &Center; }
	Dimension* getDimensions() { return &Dimensions; }

	void MoveEdges(bool Rotation);
	void MoveCenter(int RReferenceEdge, int Velocity, float DeltaTime);
	void ChangeCenterPosition(float x, float y);
	void Rotate(bool RotateLeft, float Rotation);

private:
	Position P1;
	Position P2;
	Position P3;
	Position Center;

	Dimension Dimensions;

};