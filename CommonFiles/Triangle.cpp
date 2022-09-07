#include "Triangle.h"

#include <cmath>

const float Pi = (float)3.141592;
const float Rad = Pi / 180;
int it;

Triangle::Triangle()
{

}

Triangle::~Triangle()
{
	
}

void Triangle::setPointData(float x, float y, int Angle, int Position)
{
	switch (Position)
	{
	case 1:
		P1.x = x;
		P1.y = y;
		P1.Angle = Angle;
	break;

	case 2:
		P2.x = x;
		P2.y = y;
		P2.Angle = Angle;
	break;

	case 3:
		P3.x = x;
		P3.y = y;
		P3.Angle = Angle;

		default:
			Center.x = x;
			Center.y = y;
			Center.Angle = Angle;
		break;
	}

}

void Triangle::setDimensions(float Width, float Height)
{
	Dimensions.Width = Width;
	Dimensions.Height = Height;
	Dimensions.Hypotenuse = sqrtf(powf(Width / 2.0f, 2.0f) + powf(Height / 2.0f, 2.0f));
}

void Triangle::MoveEdges(bool Rotation)
{
	if (Rotation)
	{
		P1.Rotation = P1.Angle * Rad;
		P2.Rotation = P2.Angle * Rad;
		P3.Rotation = P3.Angle * Rad;
	}

	P1.x = Center.x + cosf(P1.Rotation) * Dimensions.Hypotenuse;
	P1.y = Center.y - sinf(P1.Rotation) * Dimensions.Hypotenuse;
	P2.x = Center.x + cosf(P2.Rotation) * Dimensions.Hypotenuse;
	P2.y = Center.y - sinf(P2.Rotation) * Dimensions.Hypotenuse;
	P3.x = Center.x + cosf(P3.Rotation)* Dimensions.Hypotenuse;
	P3.y = Center.y - sinf(P3.Rotation) * Dimensions.Hypotenuse;
}

void Triangle::Rotate(bool RotateLeft, float Rotation)
{
	if (RotateLeft) 
	{
		P1.Angle += Rotation;
		P2.Angle += Rotation;
		P3.Angle += Rotation;
	}
	else
	{
		P1.Angle -= Rotation;
		P2.Angle -= Rotation;
		P3.Angle -= Rotation;
	}
}

void Triangle::MoveCenter(int ReferenceEdge, int Velocity, float DeltaTime)
{
	switch (ReferenceEdge)
	{
		case 1:
			Center.x += cosf(P1.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(P1.Rotation) * Velocity * DeltaTime;
		break;	
		
		case 2:
			Center.x += cosf(P2.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(P2.Rotation) * Velocity * DeltaTime;
		break;	
		
		case 3:
			Center.x += cosf(P3.Rotation) * Velocity * DeltaTime;
			Center.y -= sinf(P3.Rotation) * Velocity * DeltaTime;
		break;
	}
}

void Triangle::ChangeCenterPosition(float x, float y)
{
	Center.x = x;
	Center.y = y;
}
