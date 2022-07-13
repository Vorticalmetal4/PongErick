#pragma once

#include "Renderer.h"

class EnemyShip
{
public: 
	EnemyShip(Renderer* _Rend);
	~EnemyShip();
	void Update(Position* PlayerCenter);
	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setNewData(bool Left, bool _Active);
	double getCenterX() { return Center.x; }
	double getCenterY() { return Center.y; }
	double getHypotenuse() { return H; }

private:
	Renderer* Rend;
	Position P1;
	Position P2;
	Position P3;
	Position Center;
	int Width;
	int HWidth;
	int Height;
	int HHeight;
	int Velocity;
	bool Active;
	double H;
	float DeltaTime;

};