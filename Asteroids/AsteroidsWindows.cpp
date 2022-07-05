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

    int i;
    int NAsteroids = ConFile.GetInteger("Asteroid", "NAsteroids", 0);
	
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
            Asteroids[i].setActive(true);
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
                    MainPlayer.CheckCollisionWLasers(&Asteroids[i]);
                }
            }

            MainPlayer.Update();
            Rend.GenerateOutput();
        }
    }
}