#include "Wall.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"


Wall::Wall(Renderer* _Rend, float _x, float _y, float _Width, float _Height)
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

	OwnDimensions.Width = _Width;
	OwnDimensions.Height = _Height;

	P1.x = _x;
	P1.y = _y;

}

Wall::~Wall()
{

}

void Wall::Draw()
{
	Rend->DrawSimpleRect(P1.x, P1.y, OwnDimensions.Width, OwnDimensions.Height, 0, 47, 157, 255);
}