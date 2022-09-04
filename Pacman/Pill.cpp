#include "Pill.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

Pill::Pill(Renderer* _Rend, float x, float y)
	:Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

	Radius = (float)ConFile.GetInteger("Pill", "Radius", 4);
	Center.x = x;
	Center.y = y;
}

Pill::~Pill()
{

}

void Pill::Update()
{
	Rend->DrawCircle(&Center, Radius, 255, 255, 0, 255);
}