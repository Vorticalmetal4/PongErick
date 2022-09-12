#include "ClockHand.h"
#include "CommonFiles/Renderer.h"
#include <math.h>
#include <corecrt_math_defines.h>

#include <iostream>
using namespace std;

const float Rad = (float)(M_PI / 180);

ClockHand::ClockHand(int _Type, float _Size, Renderer* _Rend)
	:Size(_Size),
	Type(ClockHandType::Seconds),
	Rend(_Rend)
{
	switch (_Type) 
	{
		case 0:
			Type = Hours;
			Multiplier = 360 / 12;
			LineColor.r = 255; 
			LineColor.g = 112;
			LineColor.b = 40;
		break;

		case 1:
			Type = Minutes;
			Multiplier = 360 / 60;
			LineColor.r = LineColor.g = 0;
			LineColor.b = 255;
		break;

		default:
			Type = Seconds;
			Multiplier = 360 / 60;
			LineColor.r = LineColor.b = 0;
			LineColor.g = 255;
		break;
	}

	End.x = End.y = 0;
	LineColor.alpha = 255;

}

void ClockHand::Update(bool Pause, tm* CurrentTime, Position* SquareCenter)
{
	if (!Pause)
	{
		switch (Type)
		{
			case Hours:
				if (CurrentTime->tm_hour <= 12)
					End.Angle = CurrentTime->tm_hour * Multiplier;
				else
					End.Angle = (CurrentTime->tm_hour - 12) * Multiplier - 90;
			break;

			case Minutes:
				End.Angle = CurrentTime->tm_min * Multiplier - 90;
			break;

			case Seconds:
				End.Angle = CurrentTime->tm_sec * Multiplier - 90;
			break;
		}

		End.Angle = 360 - End.Angle;
		End.x = SquareCenter->x + cosf(End.Angle * Rad) * Size;
		End.y = SquareCenter->y - sinf(End.Angle * Rad) * Size;
	}

	Rend->DrawLine(SquareCenter, &End, LineColor.r, LineColor.g, LineColor.b, LineColor.alpha);
}