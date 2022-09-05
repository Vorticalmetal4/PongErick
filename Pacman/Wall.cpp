#include "Wall.h"
#include "CommonFiles/Renderer.h"
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

	WallColor = {0, 47, 154, 255};
}

Wall::Wall(Renderer* _Rend, float _x, float _y, float _Width, float _Height, int r, int g, int b, int alpha)
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

	OwnDimensions.Width = _Width;
	OwnDimensions.Height = _Height;

	P1.x = _x;
	P1.y = _y;

	WallColor = { r, g, b, alpha};
}

Wall::~Wall()
{

}

void Wall::Draw()
{
	Rend->DrawSimpleRect(P1.x, P1.y, OwnDimensions.Width, OwnDimensions.Height, WallColor.r, WallColor.g, WallColor.b, WallColor.alpha);
}