#include "Map.h"
#include "Renderer.h"
#include "Wall.h"
#include "Inih/cpp/INIReader.h"

Map::Map(Renderer* _Rend)
    :Rend(_Rend),
    i(0)
{

    INIReader ConFile("InitialData.ini");

    if (ConFile.ParseError() < 0)
        ConFile.PrintError("AsteroidsWindow");

    float CorridorSize = (float)ConFile.GetInteger("Wall", "CorridorSize", 24);
    float ScoreSpace = (float)ConFile.GetInteger("Map", "ScoreSpace", 20);
    float Thickness = (float)ConFile.GetInteger("Wall", "Thickness", 25);

    //Top left part of the map
    FirstSectionWallsSize = ConFile.GetInteger("Map", "FirstSectionWallsSize", 16);
    SecondSectionWallsSize = ConFile.GetInteger("Map", "SecondSectionWallsSize", 16);
    ThirdSectionWallsSize = ConFile.GetInteger("Map", "ThirdSectionWallsSize", 18);
    FourthSectionWallsSize = ConFile.GetInteger("Map", "FourthSectionWallsSize", 18);

    FirstSectionWallsSize = 16;
    FirstSectionWalls = new Wall[FirstSectionWallsSize];

    FirstSectionWalls[0] = Wall(Rend, 0, ScoreSpace, 7.5f * CorridorSize + Thickness, Thickness); //Roof - 0
    FirstSectionWalls[1] = Wall(Rend, FirstSectionWalls->getPosition()->x + FirstSectionWalls[0].getDimension()->Width, 20, Thickness / 2.0f, 2 * CorridorSize); //Intersection wall between first and second section - 1
    FirstSectionWalls[2] = Wall(Rend, 0, FirstSectionWalls[0].getPosition()->y + FirstSectionWalls[0].getDimension()->Height, Thickness, 4.5f * CorridorSize); //Left Wall - 2
    FirstSectionWalls[3] = Wall(Rend, FirstSectionWalls[2].getPosition()->x + FirstSectionWalls[2].getDimension()->Width + CorridorSize, FirstSectionWalls[0].getPosition()->y + FirstSectionWalls[0].getDimension()->Height + CorridorSize, 2 * CorridorSize, CorridorSize); //First obstacle - 3
    FirstSectionWalls[4] = Wall(Rend, FirstSectionWalls[3].getPosition()->x + FirstSectionWalls[3].getDimension()->Width + CorridorSize, FirstSectionWalls[3].getPosition()->y, 2.5f * CorridorSize, FirstSectionWalls[3].getDimension()->Height); //Second obstacle - 4
    FirstSectionWalls[5] = Wall(Rend, FirstSectionWalls[3].getPosition()->x, FirstSectionWalls[3].getPosition()->y + FirstSectionWalls[3].getDimension()->Height + CorridorSize, FirstSectionWalls[3].getDimension()->Width, CorridorSize / 2.0f); //Third Obsctacle - 5
    FirstSectionWalls[6] = Wall(Rend, 0, FirstSectionWalls[2].getPosition()->y + FirstSectionWalls[2].getDimension()->Height, FirstSectionWalls[3].getDimension()->Width + CorridorSize, Thickness);  //First horizontal left wall - 6
    FirstSectionWalls[7] = Wall(Rend, FirstSectionWalls[6].getPosition()->x + FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getPosition()->y, Thickness, 2.5f * CorridorSize);   // Second vertical left wall - 7
    FirstSectionWalls[8] = Wall(Rend, FirstSectionWalls[6].getPosition()->x, FirstSectionWalls[6].getPosition()->y + FirstSectionWalls[7].getDimension()->Height - Thickness, FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getDimension()->Height); //Second horizontal left wall - 8
    FirstSectionWalls[9] = Wall(Rend, FirstSectionWalls[5].getPosition()->x + FirstSectionWalls[5].getDimension()->Width + CorridorSize, FirstSectionWalls[5].getPosition()->y, Thickness, FirstSectionWalls[7].getDimension()->Height + CorridorSize + Thickness + 2);    //Vertical wall fourth obstable - 9
    FirstSectionWalls[10] = Wall(Rend, FirstSectionWalls[9].getPosition()->x + Thickness, FirstSectionWalls[6].getPosition()->y, 2 * CorridorSize, CorridorSize / 2.0f); //Horizontal wall fourth obstacle - 10
    FirstSectionWalls[11] = Wall(Rend, FirstSectionWalls[9].getPosition()->x + Thickness + CorridorSize, FirstSectionWalls[9].getPosition()->y, 2 * CorridorSize + 5, CorridorSize / 2.0f); //Horizontal wall intersection obstacle - 11
    FirstSectionWalls[12] = Wall(Rend, FirstSectionWalls[1].getPosition()->x, FirstSectionWalls[11].getPosition()->y, Thickness / 2.0f, 2 * CorridorSize); //Vertical wall intersection obstacle - 12
    FirstSectionWalls[13] = Wall(Rend, FirstSectionWalls[11].getPosition()->x, FirstSectionWalls[8].getPosition()->y - Thickness, FirstSectionWalls[11].getDimension()->Width - CorridorSize / 2.0f, Thickness); //Ghost's house horizontal wall - 13
    FirstSectionWalls[14] = Wall(Rend, FirstSectionWalls[13].getPosition()->x + FirstSectionWalls[13].getDimension()->Width, FirstSectionWalls[13].getPosition()->y, CorridorSize / 2.0f, Thickness, 255, 255, 255, 255);  //Ghost's house door - 14
    FirstSectionWalls[15] = Wall(Rend, FirstSectionWalls[13].getPosition()->x, FirstSectionWalls[13].getPosition()->y + FirstSectionWalls[13].getDimension()->Height, Thickness, Thickness + CorridorSize / 2.1f); //Ghost's house vertical wall - 15

    //Top right part of the map
    int SecondSectionWallsSize = 16;
    SecondSectionWalls = new Wall[SecondSectionWallsSize];

    SecondSectionWalls[0] = Wall(Rend, Rend->getWindowWidth() - FirstSectionWalls[0].getDimension()->Width, FirstSectionWalls[0].getPosition()->y, FirstSectionWalls[0].getDimension()->Width, Thickness);  //Roof - 0
    SecondSectionWalls[1] = Wall(Rend, FirstSectionWalls[1].getPosition()->x + FirstSectionWalls[1].getDimension()->Width, FirstSectionWalls[1].getPosition()->y, FirstSectionWalls[1].getDimension()->Width, FirstSectionWalls[1].getDimension()->Height); //Intersection wall between second and first section - 1
    SecondSectionWalls[2] = Wall(Rend, Rend->getWindowWidth() - Thickness, FirstSectionWalls[2].getPosition()->y, Thickness, FirstSectionWalls[2].getDimension()->Height); //Right Wall - 2
    SecondSectionWalls[3] = Wall(Rend, SecondSectionWalls[1].getPosition()->x + SecondSectionWalls[1].getDimension()->Width + CorridorSize, SecondSectionWalls[0].getPosition()->y + Thickness + CorridorSize, FirstSectionWalls[4].getDimension()->Width, FirstSectionWalls[4].getDimension()->Height); //First obstacle - 3
    SecondSectionWalls[4] = Wall(Rend, SecondSectionWalls[3].getPosition()->x + SecondSectionWalls[3].getDimension()->Width + CorridorSize, SecondSectionWalls[3].getPosition()->y, FirstSectionWalls[3].getDimension()->Width, FirstSectionWalls[3].getDimension()->Height); //Second obstacle - 4
    SecondSectionWalls[5] = Wall(Rend, SecondSectionWalls[4].getPosition()->x, SecondSectionWalls[4].getPosition()->y + SecondSectionWalls[4].getDimension()->Height + CorridorSize, SecondSectionWalls[4].getDimension()->Width, FirstSectionWalls[5].getDimension()->Height);  //Third obstacle - 5
    SecondSectionWalls[6] = Wall(Rend, Rend->getWindowWidth() - FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getPosition()->y, FirstSectionWalls[6].getDimension()->Width, FirstSectionWalls[6].getDimension()->Height); //First horizontal right wall - 6
    SecondSectionWalls[7] = Wall(Rend, SecondSectionWalls[6].getPosition()->x - Thickness, SecondSectionWalls[6].getPosition()->y, Thickness, FirstSectionWalls[7].getDimension()->Height); //Second horizontal right wall - 7
    SecondSectionWalls[8] = Wall(Rend, SecondSectionWalls[6].getPosition()->x, SecondSectionWalls[6].getPosition()->y + SecondSectionWalls[7].getDimension()->Height - Thickness, SecondSectionWalls[6].getDimension()->Width, Thickness);
    SecondSectionWalls[9] = Wall(Rend, SecondSectionWalls[5].getPosition()->x - CorridorSize - FirstSectionWalls[9].getDimension()->Width, SecondSectionWalls[5].getPosition()->y, Thickness, FirstSectionWalls[9].getDimension()->Height); //Vertical wall fourth obstacle - 9
    SecondSectionWalls[10] = Wall(Rend, SecondSectionWalls[9].getPosition()->x - FirstSectionWalls[10].getDimension()->Width, FirstSectionWalls[10].getPosition()->y, FirstSectionWalls[10].getDimension()->Width, FirstSectionWalls[10].getDimension()->Height); //Horizontal wall fourth obstacle - 10
    SecondSectionWalls[11] = Wall(Rend, FirstSectionWalls[11].getPosition()->x + FirstSectionWalls[11].getDimension()->Width + 4, FirstSectionWalls[11].getPosition()->y, FirstSectionWalls[11].getDimension()->Width, FirstSectionWalls[11].getDimension()->Height);  //Horizontal wall intersection obstacle - 11
    SecondSectionWalls[12] = Wall(Rend, FirstSectionWalls[12].getPosition()->x + FirstSectionWalls[12].getDimension()->Width, FirstSectionWalls[12].getPosition()->y, FirstSectionWalls[12].getDimension()->Width, FirstSectionWalls[12].getDimension()->Height);  //Vertical wall intersection obstacle - 12
    SecondSectionWalls[13] = Wall(Rend, FirstSectionWalls[14].getPosition()->x + FirstSectionWalls[14].getDimension()->Width, FirstSectionWalls[14].getPosition()->y, FirstSectionWalls[14].getDimension()->Width, Thickness, 255, 255, 255, 255); //Ghost's house door - 13
    SecondSectionWalls[14] = Wall(Rend, SecondSectionWalls[13].getPosition()->x + SecondSectionWalls[13].getDimension()->Width, SecondSectionWalls[13].getPosition()->y, FirstSectionWalls[13].getDimension()->Width, Thickness);  //Ghost's house horizontal wall - 14 
    SecondSectionWalls[15] = Wall(Rend, SecondSectionWalls[14].getPosition()->x + SecondSectionWalls[14].getDimension()->Width - Thickness, SecondSectionWalls[14].getPosition()->y + SecondSectionWalls->getDimension()->Height, Thickness, FirstSectionWalls[15].getDimension()->Height);   //Ghost's house vertical wall - 15

    //Bottom left part of the map
    int ThirdSectionWallsSize = 18;
    ThirdSectionWalls = new Wall[ThirdSectionWallsSize];

    ThirdSectionWalls[0] = Wall(Rend, FirstSectionWalls[6].getPosition()->x, FirstSectionWalls[8].getPosition()->y + FirstSectionWalls[6].getDimension()->Height + CorridorSize, FirstSectionWalls[6].getDimension()->Width, Thickness);   //First horizontal wall - 0
    ThirdSectionWalls[1] = Wall(Rend, FirstSectionWalls[7].getPosition()->x, ThirdSectionWalls[0].getPosition()->y, Thickness, FirstSectionWalls[7].getDimension()->Height);   //First vertical wall - 1
    ThirdSectionWalls[2] = Wall(Rend, ThirdSectionWalls[0].getPosition()->x, ThirdSectionWalls[1].getPosition()->y + ThirdSectionWalls[1].getDimension()->Height - Thickness, ThirdSectionWalls[0].getDimension()->Width, Thickness);  //Second Horizontal wall - 2
    ThirdSectionWalls[3] = Wall(Rend, ThirdSectionWalls[0].getPosition()->x, ThirdSectionWalls[2].getPosition()->y + Thickness, Thickness, 5 * CorridorSize + Thickness / 1.8f); //Second vertical wall - 3
    ThirdSectionWalls[4] = Wall(Rend, ThirdSectionWalls[3].getPosition()->x, ThirdSectionWalls[3].getPosition()->y + ThirdSectionWalls[3].getDimension()->Height, 8 * CorridorSize + Thickness, Thickness);  //Floor - 4
    ThirdSectionWalls[5] = Wall(Rend, ThirdSectionWalls[4].getPosition()->x + Thickness + CorridorSize, ThirdSectionWalls[2].getPosition()->y + CorridorSize + ThirdSectionWalls[2].getDimension()->Height, 2 * CorridorSize, Thickness);  //Horizontal wall first obstacle - 5
    ThirdSectionWalls[6] = Wall(Rend, ThirdSectionWalls[5].getPosition()->x + ThirdSectionWalls[5].getDimension()->Width - Thickness, ThirdSectionWalls[5].getPosition()->y + Thickness, Thickness, CorridorSize + Thickness); //Vertical wall first obstacle - 6
    ThirdSectionWalls[7] = Wall(Rend, ThirdSectionWalls[3].getPosition()->x + Thickness, ThirdSectionWalls[5].getPosition()->y + Thickness + CorridorSize, CorridorSize + Thickness, Thickness);  //Second obstacle - 7
    ThirdSectionWalls[8] = Wall(Rend, ThirdSectionWalls[6].getPosition()->x + ThirdSectionWalls[6].getDimension()->Width + CorridorSize, ThirdSectionWalls[5].getPosition()->y, FirstSectionWalls[4].getDimension()->Width, 0.5f * CorridorSize); //Third obstacle - 8
    ThirdSectionWalls[9] = Wall(Rend, ThirdSectionWalls[5].getPosition()->x, ThirdSectionWalls[7].getPosition()->y + ThirdSectionWalls[7].getDimension()->Height + CorridorSize, 5 * CorridorSize + Thickness, Thickness); //Horizontal wall fourth obstacle - 9
    ThirdSectionWalls[10] = Wall(Rend, ThirdSectionWalls[8].getPosition()->x, ThirdSectionWalls[8].getPosition()->y + ThirdSectionWalls[8].getDimension()->Height + CorridorSize, Thickness, 1.5f * CorridorSize); //Vertical wall fourth obstacle - 10
    ThirdSectionWalls[11] = Wall(Rend, ThirdSectionWalls[1].getPosition()->x + ThirdSectionWalls[1].getDimension()->Width + CorridorSize, ThirdSectionWalls[1].getPosition()->y, Thickness, ThirdSectionWalls[1].getDimension()->Height);  //Fifth obstacle - 11
    ThirdSectionWalls[12] = Wall(Rend, FirstSectionWalls[15].getPosition()->x, FirstSectionWalls[15].getPosition()->y + FirstSectionWalls[15].getDimension()->Height, Thickness, FirstSectionWalls[15].getDimension()->Height); //Ghost's house vertical wall - 12
    ThirdSectionWalls[13] = Wall(Rend, ThirdSectionWalls[12].getPosition()->x, ThirdSectionWalls[12].getPosition()->y + ThirdSectionWalls[12].getDimension()->Height, FirstSectionWalls[13].getDimension()->Width + FirstSectionWalls[14].getDimension()->Width, Thickness);   //Ghost's house floor - 13
    ThirdSectionWalls[14] = Wall(Rend, ThirdSectionWalls[13].getPosition()->x, ThirdSectionWalls[11].getPosition()->y + ThirdSectionWalls[11].getDimension()->Height - Thickness, ThirdSectionWalls[13].getDimension()->Width, Thickness); //Horizontal wall sixth obstacle (first instersection) - 14
    ThirdSectionWalls[15] = Wall(Rend, FirstSectionWalls[12].getPosition()->x, ThirdSectionWalls[14].getPosition()->y, FirstSectionWalls[12].getDimension()->Width, FirstSectionWalls[12].getDimension()->Height - 2); //Vertical wall sixth obstacle (first intersection) - 15
    ThirdSectionWalls[16] = Wall(Rend, ThirdSectionWalls[14].getPosition()->x, ThirdSectionWalls[7].getPosition()->y, ThirdSectionWalls[14].getDimension()->Width, Thickness);     //Horizontal wall seventh wall (second intersection) - 16
    ThirdSectionWalls[17] = Wall(Rend, ThirdSectionWalls[15].getPosition()->x, ThirdSectionWalls[16].getPosition()->y, ThirdSectionWalls[15].getDimension()->Width, ThirdSectionWalls[15].getDimension()->Height); //Vertical wall seventh wall (second intersection) - 17  

    int FourthSectionWallsSize = 18;
    FourthSectionWalls = new Wall[FourthSectionWallsSize];

    FourthSectionWalls[0] = Wall(Rend, SecondSectionWalls[6].getPosition()->x, ThirdSectionWalls[0].getPosition()->y, ThirdSectionWalls[0].getDimension()->Width, Thickness);  //First horizontal right wall - 0
    FourthSectionWalls[1] = Wall(Rend, SecondSectionWalls[7].getPosition()->x, ThirdSectionWalls[1].getPosition()->y, Thickness, ThirdSectionWalls[1].getDimension()->Height); //First vertical right wall - 1
    FourthSectionWalls[2] = Wall(Rend, SecondSectionWalls[8].getPosition()->x, ThirdSectionWalls[2].getPosition()->y, ThirdSectionWalls[2].getDimension()->Width, Thickness);  //Second horizontal right wall - 2
    FourthSectionWalls[3] = Wall(Rend, SecondSectionWalls[2].getPosition()->x, ThirdSectionWalls[3].getPosition()->y, Thickness, ThirdSectionWalls[3].getDimension()->Height); //Second vertical right wall - 3
    FourthSectionWalls[4] = Wall(Rend, ThirdSectionWalls[4].getPosition()->x + ThirdSectionWalls[4].getDimension()->Width, ThirdSectionWalls[4].getPosition()->y, ThirdSectionWalls[4].getDimension()->Width, Thickness);  //Floor - 4
    FourthSectionWalls[5] = Wall(Rend, FourthSectionWalls[1].getPosition()->x - CorridorSize - Thickness, FourthSectionWalls[1].getPosition()->y, Thickness, FourthSectionWalls[1].getDimension()->Height);    //First obstacle - 5
    FourthSectionWalls[6] = Wall(Rend, ThirdSectionWalls[14].getPosition()->x + ThirdSectionWalls[14].getDimension()->Width, ThirdSectionWalls[14].getPosition()->y, ThirdSectionWalls[14].getDimension()->Width, Thickness); //Horizontal wall second obstacle (first instersection) - 6
    FourthSectionWalls[7] = Wall(Rend, ThirdSectionWalls[15].getPosition()->x + ThirdSectionWalls[15].getDimension()->Width, FourthSectionWalls[6].getPosition()->y, ThirdSectionWalls[15].getDimension()->Width, ThirdSectionWalls[15].getDimension()->Height); //Vertical wall second obstacle (first intersection) - 7
    FourthSectionWalls[8] = Wall(Rend, ThirdSectionWalls[16].getPosition()->x + ThirdSectionWalls[16].getDimension()->Width, ThirdSectionWalls[16].getPosition()->y, ThirdSectionWalls[16].getDimension()->Width, ThirdSectionWalls[16].getDimension()->Height); //Horizontal wall third obstacle (second intersection) - 8
    FourthSectionWalls[9] = Wall(Rend, ThirdSectionWalls[17].getPosition()->x + ThirdSectionWalls[17].getDimension()->Width, FourthSectionWalls[8].getPosition()->y, ThirdSectionWalls[17].getDimension()->Width, ThirdSectionWalls[17].getDimension()->Height);  //Vertical wall third obstacle (second intersection) - 9
    FourthSectionWalls[10] = Wall(Rend, FourthSectionWalls[7].getPosition()->x + FourthSectionWalls[7].getDimension()->Width + CorridorSize, ThirdSectionWalls[8].getPosition()->y, ThirdSectionWalls[8].getDimension()->Width, Thickness);  //Fourth obstacle - 10
    FourthSectionWalls[11] = Wall(Rend, FourthSectionWalls[10].getPosition()->x + FourthSectionWalls[10].getDimension()->Width + CorridorSize, FourthSectionWalls[10].getPosition()->y, ThirdSectionWalls[5].getDimension()->Width, Thickness); //Horizontal wall fifth obstacle - 11
    FourthSectionWalls[12] = Wall(Rend, FourthSectionWalls[11].getPosition()->x, FourthSectionWalls[11].getPosition()->y + Thickness, Thickness, ThirdSectionWalls[6].getDimension()->Height); //Vertical wall fifth obstacle - 12
    FourthSectionWalls[13] = Wall(Rend, FourthSectionWalls[3].getPosition()->x - ThirdSectionWalls[7].getDimension()->Width, FourthSectionWalls[8].getPosition()->y, ThirdSectionWalls[7].getDimension()->Width, Thickness); //Sixth obstacle - 13
    FourthSectionWalls[14] = Wall(Rend, FourthSectionWalls[10].getPosition()->x, ThirdSectionWalls[9].getPosition()->y, ThirdSectionWalls[9].getDimension()->Width, Thickness); //Horizontal wall seventh obstacle - 14
    FourthSectionWalls[15] = Wall(Rend, FourthSectionWalls[10].getPosition()->x + FourthSectionWalls[10].getDimension()->Width - Thickness, ThirdSectionWalls[10].getPosition()->y, Thickness, ThirdSectionWalls[10].getDimension()->Height); //Vertical wall seventh obstacle - 15
    FourthSectionWalls[16] = Wall(Rend, ThirdSectionWalls[13].getPosition()->x + ThirdSectionWalls[13].getDimension()->Width, ThirdSectionWalls[13].getPosition()->y, ThirdSectionWalls[13].getDimension()->Width, Thickness); //Ghost's house floor - 16
    FourthSectionWalls[17] = Wall(Rend, SecondSectionWalls[15].getPosition()->x, SecondSectionWalls[15].getPosition()->y + SecondSectionWalls[15].getDimension()->Height, Thickness, SecondSectionWalls[15].getDimension()->Height); //Ghost's house wall  

    MapHeight = FirstSectionWalls[0].getDimension()->Height + FirstSectionWalls[2].getDimension()->Height + FirstSectionWalls[7].getDimension()->Height + CorridorSize / 2.0f;
    MapWidth = FourthSectionWalls[4].getDimension()->Width;

}

void Map::Draw()
{
    for (i = 0; i < FirstSectionWallsSize; i++)
        FirstSectionWalls[i].Draw();

    for (i = 0; i < SecondSectionWallsSize; i++)
        SecondSectionWalls[i].Draw();

    for (i = 0; i < ThirdSectionWallsSize; i++)
        ThirdSectionWalls[i].Draw();

    for (i = 0; i < FourthSectionWallsSize; i++)
        FourthSectionWalls[i].Draw();
}