#pragma once

#include "Renderer.h"
#include "Raycaster.h"

class EnemyShip
{
public: 
	EnemyShip(Renderer* _Rend);
	~EnemyShip();
	void Update(Position* PlayerCenter, double PlayerHypotenuse);
	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setNewData(bool Left, bool _Active);
	double getHypotenuse() { return H; }
	Position* getCenter() { return &Center; }

private:
	Raycaster Ray;
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