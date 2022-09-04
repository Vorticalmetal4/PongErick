#include "Renderer.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "Wall.h"
#include "Map.h"

#include "Inih/cpp/INIReader.h"

#include <iostream>
using namespace std;


int main()
{
    INIReader ConFile("InitialData.ini");

    if (ConFile.ParseError() < 0)
        ConFile.PrintError("AsteroidsWindow");

    Renderer Rend;

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        ConFile.GetInteger("Window", "Width", 1080),
        ConFile.GetInteger("Window", "Height", 720),
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));

    Map MainMap(&Rend);

    CollisionSystem CollisionDetector;
    Player MainPlayer(&Rend, &CollisionDetector, MainMap.getMapHeight() + ConFile.GetInteger("Map", "ScoreSpace", 20), MainMap.getMapWidth());

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            MainMap.Draw();

            switch (MainPlayer.getSection())
            {
            case 1:
                MainPlayer.Update(MainMap.getFirstSectionWalls(), MainMap.getFirstSectionWallsSize());
                break;

            case 2:
                MainPlayer.Update(MainMap.getSecondSectionWalls(), MainMap.getSecondSectionWallsSize());
                break;

            case 3:
                MainPlayer.Update(MainMap.getThirdSectionWalls(), MainMap.getThirdSectionWallsSize());
                break;

            case 4:
                MainPlayer.Update(MainMap.getFourthSectionWalls(), MainMap.getFourthSectionWallsSize());
                break;
            }

            Rend.GenerateOutput();
        }
    }

    return 0;
}