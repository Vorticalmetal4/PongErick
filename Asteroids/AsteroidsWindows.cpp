#include "Inih/cpp/INIReader.h"
#include "Renderer.h"
#include "Player.h"
#include "Asteroid.h"

#include <iostream> 
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{ 

    INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow");

    int i, j, k, t;
    int Collisions = 0;
    int NAsteroids = ConFile.GetInteger("Asteroid", "NAsteroids", 0);
    int AsteroidsMaxSize = ConFile.GetInteger("Asteroid", "MaxSize", 3);
	
    Renderer Rend;

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
                                   ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
                                   ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
                                   ConFile.GetInteger("Window", "Width", 1080),
                                   ConFile.GetInteger("Window", "Height", 700),
                                   ConFile.GetInteger("Window", "Flags", 0),
                                   ConFile.GetString("Window", "Font", "Error"));

    Player MainPlayer = Player(&Rend);
    vector<Asteroid> Asteroids;
    srand(time(NULL));

    for (i = 0; i < NAsteroids * 4; i++)
    {
        Asteroid NAsteroid = Asteroid(&Rend, rand() % Rend.getWindowWidth(), rand() % Rend.getWindowHeight(), rand() % 360);
        Asteroids.push_back(NAsteroid);
        if (i < NAsteroids)
        {
            Asteroids[i].setActive(true);
            Asteroids[i].setSize(0);
        }
    }

    if(success)
    {
        while(Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();

            for(i = 0; i < Asteroids.size(); i++)
            {
                if(Asteroids[i].getActive())
                {
                    Asteroids[i].Update();
                    if (MainPlayer.CheckCollisions(&Asteroids[i]))
                        Collisions = 1;
                    
                    for (k = i + 1; k < Asteroids.size(); k++)
                        if(Asteroids[k].getActive())
                            if (Asteroids[i].CheckCollision(&Asteroids[k]))
                            {
                                t = k;
                                Collisions = 2;
                                break;
                            }


                    while (Collisions > 0)
                    {
                        if (Collisions == 1)
                            t = i;
                        if (Asteroids[t].getSize() < AsteroidsMaxSize)
                        {
                            for (j = 0; j < Asteroids.size(); j++)
                                if (!Asteroids[j].getActive())
                                {
                                    Asteroids[j].setActive(true);
                                    Asteroids[j].setNewData(Asteroids[t].getCenterX(), Asteroids[t].getCenterY(), Asteroids[t].getAngle(), Asteroids[t].getSize(), Asteroids[t].getWidth(), Asteroids[t].getHeight(), true);
                                    Asteroids[t].setNewData(Asteroids[t].getCenterX(), Asteroids[t].getCenterY(), Asteroids[t].getAngle(), Asteroids[t].getSize(), Asteroids[t].getWidth(), Asteroids[t].getHeight(), false);
                                    Collisions--;
                                    break;
                                }

                        }
                        else
                        {
                            Collisions--;
                            Asteroids[t].setActive(false);
                        }
                    }

                }

            }

            MainPlayer.Update();
            Rend.GenerateOutput();
        }
    }
}

