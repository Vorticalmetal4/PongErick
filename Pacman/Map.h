#pragma once

class Map
{
public:
	Map(class Renderer* _Rend);

	class Wall* getFirstSectionWalls() { return FirstSectionWalls; }
	Wall* getSecondSectionWalls() { return SecondSectionWalls; }
	Wall* getThirdSectionWalls() { return ThirdSectionWalls; }
	Wall* getFourthSectionWalls() { return FourthSectionWalls; }

	int getFirstSectionWallsSize() { return FirstSectionWallsSize; }
	int getSecondSectionWallsSize() { return SecondSectionWallsSize; }
	int getThirdSectionWallsSize() { return ThirdSectionWallsSize; }
	int getFourthSectionWallsSize() { return FourthSectionWallsSize; }

	void Draw();

	float getMapHeight() { return MapHeight; }
	float getMapWidth() { return MapWidth; }

private:
	Renderer* Rend;
	Wall* FirstSectionWalls;
	Wall* SecondSectionWalls;
	Wall* ThirdSectionWalls;
	Wall* FourthSectionWalls;

	float MapHeight;
	float MapWidth;

	int FirstSectionWallsSize;
	int SecondSectionWallsSize;
	int ThirdSectionWallsSize;
	int FourthSectionWallsSize;

	int i;
};