#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "HUD.h"
#include "Power.h"
#include "../Inih/cpp/INIReader.h"


#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, int** argv) {



    INIReader ConFile("InitialData.ini");

    if (ConFile.ParseError() < 0)
        cout << "Main: Couldn't find the Configuration File" << endl;

    int PowerProbability = ConFile.GetInteger("Power", "Probability", 0);
    const int BricksColumns = 10;
    const int BricksRows = 6;
    const float BricksSeparation = 4.2;
    int BricksRemaining = BricksColumns * BricksRows;

    Renderer Rend;
    bool success = Rend.Initialize();
    Player* Player1 = new Player(&Rend);
    HUD* PHUD = new HUD(&Rend, Player1, BricksRemaining);
    Brick Bricks[BricksColumns][BricksRows];
    Ball* MainBall = new Ball(&Rend, Player1, PHUD);
    for (int i = 0; i < BricksColumns; i++)
        for (int j = 0; j < BricksRows; j++)
            Bricks[i][j].setData(&Rend, i, j, BricksSeparation);


    vector<Power*> Powers;

    srand(time(NULL));

    if (success) {
        while (Rend.getIsRunning()) {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            for (int i = 0; i < BricksColumns; i++) {
                for (int j = 0; j < BricksRows; j++) {
                    if (Bricks[i][j].getActive()) {
                        if (Bricks[i][j].CheckCollition(MainBall)) {
                            BricksRemaining--;
                            PHUD->DecBricks();
                            if ((rand() % (100) + 1) <= PowerProbability) {
                                Power* NPower = new Power(Player1, &Rend, Bricks[i][j].getXPosition(), Bricks[i][j].getYPosition() + 10);
                                Powers.push_back(NPower);
                            }
                        }
                        Bricks[i][j].Draw(j);
                        if (Player1->getLaserCount() > 0) { //Check collision with laser
                            if (Player1->CheckLasersCollition(&Bricks[i][j])) {
                                if (Player1->getPower()[0] == 'T') {    //Check if alredy exists a traitorous brick in the position of the new traitor
                                    for (int k = 0; k < BricksRows; k++) {
                                        if (k != i)
                                            if (Bricks[i][j].getXPosition() == Bricks[k][j].getXPosition() && Bricks[i][j].getYPosition() == Bricks[k][j].getYPosition())
                                                Bricks[i][j].setActive(false);
                                    }
                                }
                                else {
                                    BricksRemaining--;
                                    PHUD->DecBricks();
                                }
                            }
                        }
                        
                    }

                }
            }

            if (BricksRemaining > 0 && PHUD->getLives() > 0) {
                MainBall->Update();
                Player1->Update();

                if (Powers.size() > 0) {
                    for (int i = 0; i < Powers.size(); i++)
                        if (Powers[i]->CheckCollition())
                            Powers.erase(Powers.begin() + i);
                        else
                            Powers[i]->Update();
                }
            }

            PHUD->UpdateHUD();
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

