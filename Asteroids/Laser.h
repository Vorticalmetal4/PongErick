#pragma once

struct LaserPosition
{
	double x;
	double y;
	double Rotation;
};

class Laser
{
public:
	Laser(class Renderer*  _Rend);
	~Laser();
	void Update();

private:
	Renderer* Rend;
	LaserPosition Position;
	bool Active;
	int Width;
	int Height;
	int Velocity;
};