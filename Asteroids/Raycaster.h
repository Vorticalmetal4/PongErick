#pragma once

#include "Renderer.h"

class Raycaster
{
public: 
	Raycaster(Renderer* _Rend);
	~Raycaster();

	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setPosition(double x, double y, int _Angle, double _Rotation);
	void Update(int Velocity);
	bool CheckCollision(double PlayerX, double PlayerY, double PlayerH);

private:
	Renderer* Rend;
	bool Active;
	Position P1;
	Position P2;
	Position P3;
	Position P4;
	Position Center;
	double H;
	float DeltaTime;

};