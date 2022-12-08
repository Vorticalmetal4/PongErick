#pragma once
#include "CommonFiles/CollisionSystem.h"

class Player
{
public: 
	Player(class Renderer* _Rend, CollisionSystem* _CollisionDetector, class Map* _LevelMap);
	~Player();

	int getSection() { return Section; }
	float getRadius() { return Radius; }
	Position* getCenter() { return &Center; }

	void Update();
	void UpdateSection();

private:
	Position Center;
	Position AuxPos;
	
	Renderer* Rend;
	CollisionSystem* CollisionDetector;
	Map* LevelMap;
	class Wall* Walls;

	int MouthSize;
	int MouthSpeed;
	int Speed;
	int Section;
	int MouthIncrement;
	int SectionNWalls;

	float Radius;
	float ActualMouthSize;
	float FirstMouthAngle;
	float SecondMouthAngle;
	float DeltaTime;
	float VerticalSectionsLine;
	float HorizontalSectionsLine;

	void AdjustMouthAngles();
	void ObtainSectionWalls();
};