#include "Laser.h"
#include "Renderer.h"
#include "Inih/cpp/INIReader.h"

Laser::Laser(Renderer* _Rend)
	:Active(false),
	Rend(_Rend)
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("Laser");

	Width = ConFile.GetInteger("Ray", "Width", 0);
	Height = ConFile.GetInteger("Ray", "Height", 0);
	Velocity = ConFile.GetInteger("Ray", "Velocity", 0);
}

Laser::~Laser()
{
}

void Laser::Update()
{
}