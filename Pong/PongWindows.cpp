#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Ball.h"
#include "Paddle.h"

#include <iostream>

int main()
{

    Renderer Rend;
    INIReader ConFile("InitialData.ini");

    int WindowWidth = ConFile.GetInteger("Window", "Width", 1080);
    int WindowHeight = ConFile.GetInteger("Window", "Height", 720);
    int Thickness = ConFile.GetInteger("Paddle", "Thickness", 0);


    if (ConFile.ParseError() < 0)
        ConFile.PrintError("PongWindow");


    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        WindowWidth,
        WindowHeight,
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));


    Ball GameBall = Ball(WindowWidth / 2, WindowHeight / 2, 150, 150, Thickness);
    Paddle Player1 = Paddle(200, 300, Thickness * 4, 400, Thickness); 
    Paddle Player2 = Paddle(824, 300, Thickness * 4, 400, Thickness); 

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();


            Rend.GenerateOutput();
        }
    }

    return 0;

}