#pragma once
#include "CommonFiles/CollisionSystem.h"

enum EGhostType
{
	Red,
	Pink,
	Blue,
	Orange
};

enum EDirection
{
	Up,
	Down,
	Left,
	Right,
	None
};

struct ColorStruct 
{
	int r;
	int g;
	int b;
	int alpha;
};

class Ghost
{
public:
	Ghost(class Renderer* _Rend, CollisionSystem* _CollisionDetector, int Number, class Player* _Pacman);
	~Ghost();

	void Update();
private:
	Position FirstPoint;
	Position AuxPosition;
	Position* PlayerCurrentPosition;
	Dimension OwnDimensions;

	Renderer* Rend;
	CollisionSystem* CollisionDetector;
	Player* Pacman;

	ColorStruct Color;
	EGhostType Type;
	EDirection CurrentDirection;

	float Speed;
	float DeltaTime;
	float HHeight;
	float HWidth;
	float CurrentDistance;
	float AuxDistance;

	void SearchPath(Position* Goal);
	bool CalculateDistance(bool isInitalDistance);
};