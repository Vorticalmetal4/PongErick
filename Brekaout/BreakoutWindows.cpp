#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "HUD.h"
#include "Power.h"


#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, int** argv) {

    const int BricksColumns = 10;
    const int BricksRows = 6;
    const float BricksSeparation = 4.2;
    bool BallUp = false;

    Renderer Rend;
    bool success = Rend.Initialize();
    HUD* PHUD = new HUD(&Rend);
    Player* Player1 = new Player(&Rend);
    Brick Bricks[BricksColumns][BricksRows];
    Ball* MainBall = new Ball(&Rend, Player1, PHUD);
    for (int i = 0; i < BricksColumns; i++)
        for (int j = 0; j < BricksRows; j++)
            Bricks[i][j].setData(&Rend, i, j, BricksSeparation);

    int TotalBricks = BricksColumns * BricksRows;

    vector<Power*> Powers;

    srand(time(NULL));

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
                    if (Bricks[i][j].getActive()) {
                        if (Bricks[i][j].CheckCollition(MainBall)) {
                            TotalBricks--;
                            PHUD->IncPuntuation(100);
                            if ( (rand() % (100) + 10) <= 30){
                                Power* NPower = new Power(Player1, Powers.size() + 1, &Rend, Bricks[i][j].getXPosition(), Bricks[i][j].getYPosition() + 10);
                                Powers.push_back(NPower);
                                cout << Powers.size() << endl;
                            }   
                        }
                        Bricks[i][j].Draw(j);
                    }      
                }
            MainBall->Update();
            Player1->Update();

            if (Powers.size() > 0) {
                for (int i = 0; i < Powers.size(); i++)
                    if (Powers[i]->CheckCollition())
                        Powers.erase(Powers.begin() + i);
                    else
                        Powers[i]->Update();
            }

            PHUD->UpdateHUD();
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

