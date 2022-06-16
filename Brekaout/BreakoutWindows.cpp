#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "HUD.h"
#include "Power.h"
#include "Ray.h"
#include "Inih/cpp/INIReader.h"

#include <vector>
#include <ctime>

int main(int argc, int** argv) 
{

    INIReader ConFile("InitialData.ini"); // esta bien, utilizar una biblioteca externa para un proposito tan sencillo es un exceso. puedes hacerlo tu mismo de forma muy sencilla

    if (ConFile.ParseError() < 0)
        ConFile.PrintError("BreakoutWindow"); // Como reemplazarias el string "Main:" y hacerlo generico en cualquier otro archivo o funcion?
    
    Renderer Rend;
    int PowerProbability = ConFile.GetInteger("Power", "Probability", 0);
    const int BricksColumns = ConFile.GetInteger("Brick", "BricksColumns", 0); //Debe ser posible configurarlo en el ini
    const int BricksRows = ConFile.GetInteger("Brick", "BricksRows", 0);

    int i, j, k;
    GameData Data;
    Data.BricksRemaining = BricksColumns * BricksRows;
    Data.Lives = ConFile.GetInteger("HUD", "Lives", 0);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
                                   ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
                                   ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
                                   ConFile.GetInteger("Window", "Width", 1080),
                                   ConFile.GetInteger("Window", "Height", 700),
                                   ConFile.GetInteger("Window", "Flags", 0),
                                   ConFile.GetString("Window", "Font", "Error"));

    const float BricksSeparation = (Rend.getWindowWidth() - BricksColumns * ConFile.GetInteger("Brick", "width", 97)) / BricksColumns;
    Ray PlayersRay = Ray();
    Player Player1 = Player(&Rend, &PlayersRay); // memory leak, realmente necesitas un pointer? 
    HUD PHUD = HUD(&Rend, &Player1); // memory leak, realmente necesitas un pointer? 
    Ball MainBall = Ball(&Rend, &Player1); // memory leak, realmente necesitas un pointer? 

    vector<vector<Brick>> Bricks;

    for (i = 0; i < BricksColumns; i++)
    {
        vector<Brick> BricksTem;
        for(j = 0; j < BricksRows; j++)
        {
            Brick BrickT = Brick(&Rend, i, j, BricksSeparation);
            BricksTem.push_back(BrickT);
        }

        Bricks.push_back(BricksTem);
    }


    vector<Power> Powers; // memory leak
    for(i = 0; i < 3; i++)
    {
        Power NPower = Power(&Player1, &Rend);
        Powers.push_back(NPower);
    }

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
                        if (Bricks[i][j].CheckCollition(&MainBall)) 
                        {
                            if(Bricks[i][j].getTraitor() == false)
                                Data.BricksRemaining--;
                            if ((rand() % (100) + 1) <= PowerProbability)
                            {
                                for (k = 0; k < Powers.size(); k++) 
                                {
                                    if (Powers[k].getActive() == false)
                                    {
                                        Powers[k].SetData(Bricks[i][j].getXPosition(), Bricks[i][j].getYPosition() + 10, true);
                                        break;
                                    }
                                }
                                
                            }
                        }
                        Bricks[i][j].Draw(j);
   
                        if (Player1.CheckLasersCollition(&Bricks[i][j])) 
                        {
                            if (Player1.getPower() == 'T') 
                            {    //Check if alredy exists a traitorous brick in the position of the new traitor
                                Bricks[i][j].setTraitor(true);
                                for (k = 0; k < BricksRows; k++) 
                                {
                                    if (k != j)
                                        if (Bricks[i][j].getXPosition() == Bricks[i][k].getXPosition() && Bricks[i][j].getYPosition() == Bricks[i][k].getYPosition()) {
                                            Bricks[i][j].setActive(false);
                                        }
                                }
                            }

                            Player1.NoPower();
                            Data.BricksRemaining--;
                        }
                        
                    }

                }
            }

            if (Data.BricksRemaining > 0 && Data.Lives > 0)
            {
                if (MainBall.Update(PHUD.getPause()) == false)
                    Data.Lives--;

                Player1.Update(PHUD.getPause());

                for (i = 0; i < Powers.size(); i++)
                {
                    if (Powers[i].getActive())
                    {
                        if (Powers[i].CheckCollision(PHUD.getPause()))
                            Powers[i].SetData(-50, -50, false);
                        else
                            Powers[i].Update();
                    }
                }
                
            }

            PHUD.UpdateHUD(Data);
            Rend.GenerateOutput();
        }
    }
        
    Rend.FreeMemory();
    Rend.Shutdown();

    return 0;
}

