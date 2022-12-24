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
	Ghost(class Renderer* _Rend, CollisionSystem* _CollisionDetector, int Number, class Player* _Pacman, class Map* _LevelMap);
	~Ghost();

	void Update();
private:
	Position FirstPoint;
	//Position AuxPosition;
	//Position AuxPosition2;
	Position Center;
	Position* PlayerCurrentPosition;
	Dimension OwnDimensions;

	Renderer* Rend;
	CollisionSystem* CollisionDetector;
	Player* Pacman;
	Map* LevelMap;
	class Wall* Walls;

	ColorStruct Color;
	EGhostType Type;
	EDirection MovementDirection;

	int SectionWallsNumber;
	int Section;
	int i;
	int SearchPathIterations;

	float VerticalSectionsLine;
	float HorizontalSectionsLine;
	float Speed;
	float DeltaTime;
	float HHeight;
	float HWidth;
	// CurrentDistance;
	//float AuxDistance;
	float MovementIncrement;

	bool isInitialDistance;

	//void SearchPath(Position* Goal);
	void ObtainSectionWalls();
	void UpdateSection();
	Position Move(EDirection NewDirection, Position CurrentPosition);
	float CalculateDistance(Position* Goal, Position* AuxPosition);
	float SearchPath(Position* Goal, Position RecPosition, int Iterations);
	bool CheckCollisionWithWalls(Position* AuxPosition2);
};