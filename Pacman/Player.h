#pragma once
#include "CollisionSystem.h"

class Player
{
public: 
	Player(class Renderer* _Rend, CollisionSystem* _CollisionDetector, float _VerticalSectionsLine, float _HorizontaSectionsLine);
	~Player();

	int getSection() { return Section; }
	int getRadius() { return Radius; }
	Position* getCenter() { return &Center; }

	void Update(class Wall* Walls, int NWalls);

private:
	Position Center;
	Position AuxPos;
	
	Renderer* Rend;

	CollisionSystem CollisionDetector;

	int MouthSize;
	int MouthSpeed;
	int Speed;
	int Section;
	int MouthIncrement;

	float Radius;
	float ActualMouthSize;
	float FirstMouthAngle;
	float SecondMouthAngle;
	float DeltaTime;
	float VerticalSectionsLine;
	float HorizontalSectionsLine;

	void AdjustMouthAngles();
	void UpdateSection();
};