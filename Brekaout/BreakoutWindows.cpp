#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"


int main(int argc, int **argv){

    const int BricksColumns = 10;
    const int BricksRows = 6;
    const float BricksSeparation = 4.2;
    bool BallUp = false;

    Renderer Rend;
    bool success = Rend.Initialize();
    Player* Player1 = new Player(&Rend);
    Brick Bricks[BricksColumns][BricksRows];
    Ball* MainBall = new Ball(&Rend, Player1);
    for (int i = 0; i < BricksColumns; i++)
        for (int j = 0; j < BricksRows; j++)
            Bricks[i][j].setData(&Rend, i, j, BricksSeparation);
    


    if (success) {
        while (Rend.getmIsRunning()) {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            if (MainBall->getYPosition() < Rend.getWindowHeight() / 2)
                BallUp = true;
            else
                BallUp = false;
            for (int i = 0; i < BricksColumns; i++)
                for (int j = 0; j < BricksRows; j++) {
                    //if (BallUp)
                        Bricks[i][j].CheckCollition(MainBall);
                    Bricks[i][j].Draw(j);
                }
            MainBall->Update();
            Player1->Update();
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

