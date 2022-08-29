#include "Renderer.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "Wall.h"

#include "Inih/cpp/INIReader.h"
#include "Unity/unity.h"

#include <iostream>
using namespace std;

void Test_MouthAngles()
{
    int _Angle = 0;
    int _FirstMouthAngle;
    int _MouthSize = 30;

    if (_Angle > 0)
        _FirstMouthAngle = _Angle - _MouthSize;

    else
        _FirstMouthAngle = 360 - _MouthSize;

    TEST_ASSERT_MESSAGE(330 == _FirstMouthAngle, "The Mouth Angle isn't zero");
}

int main()
{
	INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

    int i;
    int FirstSectionWallsSize = 13;
    float CorridorSize = ConFile.GetInteger("Player", "Radius", 10) * 3.0f;
    float ScoreSpace = (float)ConFile.GetInteger("Wall", "ScoreSpace", 20);
    float Thickness = (float)ConFile.GetInteger("Wall", "Thickness", 25);

    Renderer Rend;
    CollisionSystem CollisionDetector;
    Player MainPlayer(&Rend);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        ConFile.GetInteger("Window", "Width", 1080),
        ConFile.GetInteger("Window", "Height", 700),
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));
    
    Wall* FirstSectionWalls = new Wall[FirstSectionWallsSize];

    FirstSectionWalls[0] = Wall(&Rend, 0, ScoreSpace, 7.5f * CorridorSize + Thickness, Thickness); //Roof - 0
    FirstSectionWalls[1] = Wall(&Rend, FirstSectionWalls->getPosition()->x + FirstSectionWalls[0].getDimension()->Width, 20, Thickness / 2.0f, 2 *  CorridorSize); //Intersection wall between first and second section - 1
    FirstSectionWalls[2] = Wall(&Rend, 0, FirstSectionWalls[0].getPosition()->y + FirstSectionWalls[0].getDimension()->Height, Thickness, 5.5f * CorridorSize); //Left Wall - 2
    FirstSectionWalls[3] = Wall(&Rend, FirstSectionWalls[2].getPosition()->x + FirstSectionWalls[2].getDimension()->Width + CorridorSize, FirstSectionWalls[0].getPosition()->y + FirstSectionWalls[0].getDimension()->Height + CorridorSize, 2 * CorridorSize, 1.5f * CorridorSize); //First obstacle - 3
    FirstSectionWalls[4] = Wall(&Rend, FirstSectionWalls[3].getPosition()->x + FirstSectionWalls[3].getDimension()->Width + CorridorSize, FirstSectionWalls[3].getPosition()->y, 2.5f * CorridorSize, FirstSectionWalls[3].getDimension()->Height); //Second obstacle - 4
    FirstSectionWalls[5] = Wall(&Rend, FirstSectionWalls[3].getPosition()->x, FirstSectionWalls[3].getPosition()->y + FirstSectionWalls[3].getDimension()->Height + CorridorSize, FirstSectionWalls[3].getDimension()->Width, CorridorSize); //Third Obsctacle - 5
    FirstSectionWalls[6] = Wall(&Rend, 0, FirstSectionWalls[2].getPosition()->y + FirstSectionWalls[2].getDimension()->Height, FirstSectionWalls[3].getDimension()->Width + CorridorSize, Thickness);  //First horizontal left wall - 6
    FirstSectionWalls[7] = Wall(&Rend, FirstSectionWalls[6].getPosition()->x + FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getPosition()->y, Thickness, 2.5f * CorridorSize);   // Second vertical left wall - 7
    FirstSectionWalls[8] = Wall(&Rend, FirstSectionWalls[6].getPosition()->x, FirstSectionWalls[6].getPosition()->y + FirstSectionWalls[7].getDimension()->Height - Thickness, FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getDimension()->Height); //Second horizontal left wall - 8
    FirstSectionWalls[9] = Wall(&Rend, FirstSectionWalls[5].getPosition()->x + FirstSectionWalls[5].getDimension()->Width + CorridorSize, FirstSectionWalls[5].getPosition()->y, Thickness, FirstSectionWalls[7].getDimension()->Height + 2 * CorridorSize);    //Vertical wall fourth obstable - 9
    FirstSectionWalls[10] = Wall(&Rend, FirstSectionWalls[9].getPosition()->x + Thickness, FirstSectionWalls[6].getPosition()->y, 2 * CorridorSize, CorridorSize); //Horizontal wall fourth obstacle - 10
    FirstSectionWalls[11] = Wall(&Rend, FirstSectionWalls[9].getPosition()->x + Thickness + CorridorSize, FirstSectionWalls[9].getPosition()->y, 2 * CorridorSize + 5, CorridorSize); //Horizontal wall intersection obstacle - 11
    FirstSectionWalls[12] = Wall(&Rend, FirstSectionWalls[1].getPosition()->x, FirstSectionWalls[11].getPosition()->y, Thickness / 2.0f, 3 * CorridorSize); //Vertical wall intersection obstacle - 12

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            for (i = 0; i < FirstSectionWallsSize; i++)
                FirstSectionWalls[i].Draw();

            MainPlayer.Update();

            Rend.GenerateOutput();
        }
    }

    UNITY_BEGIN();

    RUN_TEST(Test_MouthAngles);

    UNITY_END();

	return 0;
}