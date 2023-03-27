#include "CommonFiles/Renderer.h"
#include "CommonFiles/CollisionSystem.h"
#include "Inih/cpp/INIReader.h"
#include "Ball.h"
#include "Paddle.h"

int main()
{

    Renderer Rend;
    CollisionSystem CollisionDetector;
    INIReader ConFile("InitialData.ini");

    if (ConFile.ParseError() < 0)
        ConFile.PrintError("PongWindow could not find the ConFile");

    int WindowWidth = ConFile.GetInteger("Window", "Width", 1080);
    int WindowHeight = ConFile.GetInteger("Window", "Height", 720);
    int Thickness = ConFile.GetInteger("Paddle", "Thickness", 0);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
        ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
        ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
        WindowWidth,
        WindowHeight,
        ConFile.GetInteger("Window", "Flags", 0),
        ConFile.GetString("Window", "Font", "Error"));


    Ball GameBall = Ball(&Rend);
    Paddle Player1 = Paddle(&Rend,&CollisionDetector, &GameBall, true); 
    Paddle Player2 = Paddle(&Rend, &CollisionDetector, &GameBall, false); 
    Player1.setOtherPaddle(&Player2);
    Player2.setOtherPaddle(&Player1);

    if (success)
    {
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            GameBall.Update();

            Player1.Update();
            Player2.Update();

            Rend.GenerateOutput();
        }
    }

    return 0;

}