#pragma once 

#include "CollisionSystem.h"
#include <string>
using namespace std;

typedef unsigned char Uint8;

class Renderer
{
public:
    Renderer(void);

    bool getIsRunning() { return mIsRunning; }
    float getDeltaTime() { return deltaTime; }
    int getWindowHeight() { return WindowHeight; }
    int getWindowWidth() { return WindowWidth; }

    bool Initialize(string Name, int TLXCoordinate, int TPYCoordinate, int Width, int Height, int Flags, string FName);
    bool CheckPause();
    bool CheckReset();
    void Shutdown();
    void ProcessInput();
    void UpdateGame();
    void ClearRender();
    void GenerateOutput();
    void Write(char* NText, int TextW, int TextH, float TextX, float TextY);
    void Write(char* NText, int TextW, int TextH, float TextX, float TextY, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
    void DrawSimpleRect(float x, float y, float width, float height, int r, int g, int b, int alpha);
    void DrawRect(Position* P1, Position* P2, Position* P3, Position* P4, int r, int g, int b, int alpha);
    void DrawTriangle(Position* P1, Position* P2, Position* P3, int r, int g, int b, int alpha);
    void DrawLine(Position* P1, Position* P2, int r, int g, int b, int alpha);
    void DrawIncompleteCircle(Position* Center, int Radius, int r, int g, int b, int alpha, float FirstSpaceAngle, float SecondSpaceAngle);
    void DrawCircle(Position* Center, int Radius, int r, int g, int b, int alpha);
    void FreeMemory();
    char CheckMovement();


private:

    bool mIsRunning;

    float deltaTime;
    float mTicksCount;

    int PauseCounter;
    int WindowHeight;
    int WindowWidth;

    char* FText;

    string FontName;


};
