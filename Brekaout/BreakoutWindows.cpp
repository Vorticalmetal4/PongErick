#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "HUD.h"
#include "Power.h"
#include "../Inih/cpp/INIReader.h"

#include <vector>
#include <ctime>

int main(int argc, int** argv) 
{

    INIReader ConFile("InitialData.ini"); // esta bien, utilizar una biblioteca externa para un proposito tan sencillo es un exceso. puedes hacerlo tu mismo de forma muy sencilla

    if (ConFile.ParseError() < 0)
        ConFile.PrintError("BreakoutWindow"); // Como reemplazarias el string "Main:" y hacerlo generico en cualquier otro archivo o funcion?

    int PowerProbability = ConFile.GetInteger("Power", "Probability", 0);
    const int BricksColumns = 10; // deberia ser posible configurarlo en el ini
    const int BricksRows = 6;
    const float BricksSeparation = 4.2;
    int i, j, k;
    GameData Data;
    Data.BricksRemaining = BricksColumns * BricksRows;
    Data.Lives = 5;

    Renderer Rend;
    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"), 
                                   ConFile.GetInteger("Window", "TopLeftXCoordinate", 0),
                                   ConFile.GetInteger("Window", "TopLeftYCoordinate", 0),
                                   ConFile.GetInteger("Window", "Width", 0),
                                   ConFile.GetInteger("Window", "Height", 0),
                                   ConFile.GetInteger("Window", "Flags", 0));
    Player* Player1 = new Player(&Rend); // memory leak, realmente necesitas un pointer? 
    HUD* PHUD = new HUD(&Rend, Player1); // memory leak, realmente necesitas un pointer? 
    Brick Bricks[BricksColumns][BricksRows];
    Ball* MainBall = new Ball(&Rend, Player1); // memory leak, realmente necesitas un pointer? 
    for (int i = 0; i < BricksColumns; i++)
        for (int j = 0; j < BricksRows; j++)
            Bricks[i][j].setData(&Rend, i, j, BricksSeparation);


    vector<Power*> Powers; // memory leak

    srand(time(NULL));

    if (success)
    {
        // La memoria principal de tu programa se incremente con el tiempo, identifica porque y arreglalo
        while (Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            for (i = 0; i < BricksColumns; i++)
            { // indentacion tipo Java, recuerdo que esto no es lo comun en los proyectos 
                for (j = 0; j < BricksRows; j++)
                {
                    if (Bricks[i][j].getActive())
                    {
                        if (Bricks[i][j].CheckCollition(MainBall)) 
                        {
                            Data.BricksRemaining--;
                            if ((rand() % (100) + 1) <= PowerProbability)
                            {
                                Power* NPower = new Power(Player1, &Rend, Bricks[i][j].getXPosition(), Bricks[i][j].getYPosition() + 10);
                                Powers.push_back(NPower);
                            }
                        }
                        Bricks[i][j].Draw(j);
                        if (Player1->getLaserCount() > 0)
                        { //Check collision with laser
                            if (Player1->CheckLasersCollition(&Bricks[i][j])) 
                            {
                                if (Player1->getPower()[0] == 'T') 
                                {    //Check if alredy exists a traitorous brick in the position of the new traitor
                                    for (k = 0; k < BricksRows; k++) 
                                    {
                                        if (k != i)
                                            if (Bricks[i][j].getXPosition() == Bricks[k][j].getXPosition() && Bricks[i][j].getYPosition() == Bricks[k][j].getYPosition())
                                                Bricks[i][j].setActive(false);
                                    }
                                }
                                 Data.BricksRemaining--;
                            }
                        }
                        
                    }

                }
            }

            if (Data.BricksRemaining > 0 && Data.Lives > 0) 
            {
                if (MainBall->Update() == false)
                    Data.Lives--;

                Player1->Update();

                if (Powers.size() > 0) 
                {
                    for (i = 0; i < Powers.size(); i++)
                        if (Powers[i]->CheckCollision())
                            Powers.erase(Powers.begin() + i);
                        else
                            Powers[i]->Update();
                }
            }

            PHUD->UpdateHUD(Data);
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

