#include "CommonFiles/Renderer.h"
#include "Inih/cpp/INIReader.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

#include <iostream>

int main()
{

    Renderer Rend;
    INIReader ConFile("InitialData.ini");

    int WindowWidth = ConFile.GetInteger("Window", "Width", 1080);
    int WindowHeight = ConFile.GetInteger("Window", "Height", 720);
    int Thickness = ConFile.GetInteger("Paddle", "Thickness", 0);


    if (ConFile.ParseError() < 0)
        ConFile.PrintError("PongWindow could not find the ConFile");


    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        WindowWidth,
        WindowHeight,
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));


    Ball GameBall = Ball(&Rend);
    Paddle Player1 = Paddle(&Rend, &GameBall, true); 
    Paddle Player2 = Paddle(&Rend, &GameBall, false); 
    Score Sc = Score();

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            Player1.Update();
            Player2.Update();

            GameBall.Update();

            Rend.GenerateOutput();
        }
    }

    return 0;

}