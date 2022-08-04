#pragma once

#include "Renderer.h"
#include "Raycaster.h"

class EnemyShip
{
public: 
	EnemyShip(void) = default;
	EnemyShip(Renderer* _Rend);
	~EnemyShip();
	void Update(Position* PlayerCenter, double PlayerHypotenuse, bool Pause);
	bool getActive() { return Active; }
	void setActive(bool _Active) { Active = _Active; }
	void setNewData(bool Left, bool _Active);
	float getHypotenuse() { return H; }
	Position* getCenter() { return &Center; }

private:
	Raycaster Ray;
	Renderer* Rend;
	Position P1;
	Position P2;
	Position P3;
	Position Center;
	int Width;
	float HWidth;
	int Height;
	float HHeight;
	int Velocity;
	bool Active;
	float H;
	float DeltaTime;
	bool wasPlayerUp;
	bool wasPlayerLeft;
	bool ChangeDirection;
	bool TurnLeft;
};