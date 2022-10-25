#pragma once
#include "CommonFiles//CollisionSystem.h"

#include <ctime>
struct Color
{
	int r;
	int g;
	int b;
	int alpha;
};

enum ClockHandType
{
	Hours,
	Minutes,
	Seconds
};

class ClockHand
{
public:
	ClockHand() = default;
	ClockHand(int _Type, float _Size, class Renderer* _Rend);
	~ClockHand() = default;

	void setSize(float NewSize) { Size = NewSize; }
	void Update(bool Pause, tm* CurrentTime, Position* SquareCenter);

	Position* getEnd() { return &End; }

private:
	Renderer* Rend;
	Position End;
	float Size;
	float Multiplier;
	ClockHandType Type;
	Color LineColor;
	
};