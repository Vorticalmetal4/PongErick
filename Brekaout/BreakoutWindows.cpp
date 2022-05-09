#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"


int main(int argc, int **argv){

    const int BricksColumns = 10;
    const int BricksRows = 6;
    const float BricksSeparation = 4.2;

    Renderer Rend;
    bool success = Rend.Initialize();
    Player* Player1 = new Player(&Rend);
    Ball* MainBall = new Ball(&Rend, Player1);
    Brick Bricks[BricksColumns][BricksRows];
    for (int i = 0; i < BricksColumns; i++)
        for(int j = 0; j < BricksRows; j++)
            Bricks[i][j].setData(&Rend, i, j, BricksSeparation);
    


    if (success) {
        while (Rend.getmIsRunning()) {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            for (int i = 0; i < BricksColumns; i++)
                for(int j = 0; j < BricksRows; j++)
                    Bricks[i][j].Draw(j);
            MainBall->Update();
            Player1->Update();
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

