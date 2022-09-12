#include "Inih/cpp/INIReader.h"
#include "CommonFiles/Renderer.h"
#include "Player.h"
#include "Asteroid.h"
#include "HUD.h"
#include "EnemyShip.h"
#include "CommonFiles/CollisionSystem.h"

#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
using namespace std;


int main()
{ 

    INIReader ConFile("InitialData.ini");

	if (ConFile.ParseError() < 0)
		ConFile.PrintError("AsteroidsWindow: ConFile Failed"); // NOTE(isaveg): error report is not clear

    int i, j, k;
    int Collisions = 0;
    int NAsteroids = ConFile.GetInteger("Asteroid", "NAsteroids", 0);
    int AsteroidsMaxSize = ConFile.GetInteger("Asteroid", "MaxSize", 3);
    bool ResetAsteroids = false;
    bool ResetGame = false;

    /*auto Start = std::chrono::system_clock::now();
    auto Current = std::chrono::system_clock::now();
    std::chrono::duration<float>CurrentSeconds = Current - Start;*/

    time_t CurrentTime;
    struct tm CurrentTimeStruct;

    Renderer Rend;
    HUDData GameData;
    CollisionSystem CollisionDetector;

    bool Pause;

    int AsteroidWidth = ConFile.GetInteger("Asteroid", "Width", 1);
    int AsteroidHeight = ConFile.GetInteger("Asteroid", "Height", 1);
    int AsteroidVelocity = ConFile.GetInteger("Asteroid", "Velocity", 1);
    int SpawnSeparation = 15;

    GameData.Lives = ConFile.GetInteger("HUD", "Lives", 0);
    GameData.Score = 0;
    int Points = ConFile.GetInteger("HUD", "PointsPerAsteroid", 0);
    int NEnemies = ConFile.GetInteger("EnemyShip", "NEnemies", 0);
    int EnemyProb = ConFile.GetInteger("EnemyShip", "EnemyProb", 0);
    int EnemyPoints = ConFile.GetInteger("EnemyShip", "Points", 0);

    bool success = Rend.Initialize(ConFile.GetString("Window", "Name", "Error"),
                                   ConFile.GetInteger("Window", "TopLeftXCoordinate", 100),
                                   ConFile.GetInteger("Window", "TopLeftYCoordinate", 20),
                                   ConFile.GetInteger("Window", "Width", 1080),
                                   ConFile.GetInteger("Window", "Height", 700),
                                   ConFile.GetInteger("Window", "Flags", 0),
                                   ConFile.GetString("Window", "Font", "Error"));
    
    HUD MainHUD = HUD(&Rend);
    Player MainPlayer = Player(&Rend, &CollisionDetector);

    srand((unsigned int)time(NULL));

    int TotalAsteroids = (int)(NAsteroids * pow(2, AsteroidsMaxSize));

    Asteroid* Asteroids = new Asteroid[TotalAsteroids];
    EnemyShip* Enemies = new EnemyShip[NEnemies];


    for (i = 0; i < TotalAsteroids; i++)
    {
        Asteroids[i] = Asteroid(&Rend, (float)(AsteroidWidth + SpawnSeparation + rand() % (Rend.getWindowWidth() - 2 * (AsteroidWidth + SpawnSeparation))), (float)(AsteroidHeight + SpawnSeparation + rand() % (Rend.getWindowHeight() - 2 * (AsteroidHeight + SpawnSeparation))), (float)(rand() % 360));  // NOTE(isaveg): Too long lines, split in different lines or create a struct to compact
        
        if (i < NAsteroids)
        {
            Asteroids[i].setActive(true);
            Asteroids[i].setSize(0);
            j = 0;
            while(j < i)
            {
                if (CollisionDetector.Square_Square(Asteroids[i].getP1(), Asteroids[j].getP1(), Asteroids[i].getDimensions(), Asteroids[j].getDimensions()))
                {
                    Asteroids[i].UpdateData((float)(AsteroidWidth + SpawnSeparation + rand() % (Rend.getWindowWidth() - 2 * (AsteroidWidth + SpawnSeparation))), (float)(AsteroidHeight + SpawnSeparation + rand() % (Rend.getWindowHeight() - 2 * (AsteroidHeight + SpawnSeparation))), Asteroids[i].getAngle()); // NOTE(isaveg): Too long lines, split in different lines or create a struct to compact
                    j = 0;
                }
                else
                    j++;
            }
        }
    }

    for(i = 0; i < NEnemies; i++)
        Enemies[i] = EnemyShip(&Rend);


    if(success)
    {
        while(Rend.getIsRunning())
        {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            Pause = MainHUD.getPause();
            ResetGame = MainHUD.getReset();

            /*Current = std::chrono::system_clock::now();
            std::chrono::duration<float>CurrentSeconds = Current - Start;*/

            time(&CurrentTime);
            localtime_s(&CurrentTimeStruct, &CurrentTime);

            for(i = 0; i < TotalAsteroids; i++)
            {
                if(Asteroids[i].getActive())
                {
                    Asteroids[i].Update(Pause, &CurrentTimeStruct);

                    if (!Pause)
                    {
                        if (MainPlayer.CheckCollisions(Asteroids[i].getCenter(), Asteroids[i].getHypotenuse()))  //Collision between player and asteroids
                            GameData.Lives--;

                        if (MainPlayer.CheckLasersCollisions(Asteroids[i].getP1(), Asteroids[i].getDimensions(), true))
                        {
                            Collisions = 1;
                            Asteroids[i].setLastObjectHitted(-1);
                            if(GameData.Lives > 0)
                                GameData.Score += Points * (Asteroids[i].getSize() + 1);
                            if (rand() % 101 <= EnemyProb)
                            {
                                for (k = 0; k < NEnemies; k++)
                                {
                                    if (!Enemies[k].getActive())
                                    {
                                        if (rand() % 2 == 1)
                                            Enemies[k].setNewData(true, true);
                                        else
                                            Enemies[k].setNewData(false, true);
                                        break;
                                    }

                                }
                            }
                        }


                        for (k = i + 1; k < TotalAsteroids; k++)
                            if (Asteroids[k].getActive())
                                if (CollisionDetector.Square_Square(Asteroids[i].getP1(), Asteroids[k].getP1(), Asteroids[i].getDimensions(), Asteroids[k].getDimensions()))
                                {
                                    Asteroids[i].ChangeDirection( k + 4); //Increase of four because we have four "walls" in the screen
                                    Asteroids[k].ChangeDirection( i + 4);
                                }

                        if (Collisions > 0)
                        {
                            if (Asteroids[i].getSize() < AsteroidsMaxSize)
                            {
                                for (j = 0; j < TotalAsteroids; j++)
                                    if (!Asteroids[j].getActive())
                                    {
                                        Asteroids[j].setActive(true);
                                        Asteroids[j].setNewData(Asteroids[i].getCenter(), Asteroids[i].getSize(), Asteroids[i].getDimensions(), true, Asteroids[i].getVelocity()); //Create a new Asteroid
                                        Asteroids[i].setNewData(Asteroids[i].getCenter(), Asteroids[i].getSize(), Asteroids[i].getDimensions(), false, Asteroids[i].getVelocity()); //Decrease the size of the destroyed asteroid
                                        break;
                                    }

                            }
                            else
                                Asteroids[i].setActive(false); 
                            Collisions--;
                        }
                    }
                }

                
            }

            for (j = 0; j < NEnemies; j++)
            {
                if (Enemies[j].getActive())
                {
                    Enemies[j].Update(MainPlayer.getCenter(), MainPlayer.getHypotenuse(), Pause);
                    if (!Pause)
                    {
                        if (MainPlayer.CheckCollisions(Enemies[j].getCenter(), Enemies[j].getHypotenuse()))
                        {
                            GameData.Lives--;
                            Enemies[j].setActive(false);
                        }
                        if (MainPlayer.CheckLasersCollisions(Enemies[j].getCenter(), Enemies[j].getDimensions(), false))
                        {
                            if(GameData.Lives > 0)
                                GameData.Score += EnemyPoints;
                            Enemies[j].setActive(false);
                        }
                    }
                }
            }

            GameData.Invincibility = MainPlayer.getInvincibiliy();
            MainHUD.Update(&GameData);
            if (GameData.Lives > 0)
                MainPlayer.Update(Pause);
            
            for (i = 0; i < TotalAsteroids; i++)
                if (Asteroids[i].getActive())
                {
                    ResetAsteroids = false;
                    break;
                }

            if(ResetGame && GameData.Lives <= 0)
            {
                ResetAsteroids = true;
                GameData.Lives = ConFile.GetInteger("HUD", "Lives", 0);
                GameData.Score = 0;
                for (i = 0; i < TotalAsteroids; i++)
                    Asteroids[i].setActive(false);
                for (i = 0; i < NEnemies; i++)
                    Enemies[i].setActive(false);
                MainPlayer.ResetLasers();
                MainHUD.ResetHUD(false);
            }


            if(ResetAsteroids)
                for(i = 0; i < NAsteroids; i++)
                    Asteroids[i].setBigAsteroid((float)AsteroidWidth, (float)AsteroidHeight, (float)(AsteroidWidth + rand() % Rend.getWindowWidth() - AsteroidWidth), (float)(AsteroidHeight + rand() % Rend.getWindowHeight() - AsteroidHeight), AsteroidVelocity);
            

            ResetAsteroids = true;

            Rend.GenerateOutput();

        }

        Rend.FreeMemory();
        MainHUD.FreeMemory();
    }
}

