#include "CommonFiles/CollisionSystem.h"
#include "CommonFiles/Renderer.h"
#include "Player.h"
#include "Wall.h"
#include "Map.h"
#include "Ghost.h"

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
    Player Pacman(&Rend, &CollisionDetector, &MainMap);
    Ghost Blinky(&Rend, &CollisionDetector, 0,&Pacman);

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            MainMap.Draw();

            Pacman.Update();

            Blinky.Update();


            Rend.GenerateOutput();
        }
    }

    return 0;
}