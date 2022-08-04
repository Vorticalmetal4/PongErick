#pragma once

#pragma once 
#pragma once 

#include <string>
using namespace std;

typedef unsigned char Uint8;

struct Position
{
    float x;
    float y;
    int Angle;
    float Rotation;
};

class Renderer
{
public:
    Renderer(void);

    bool getIsRunning() { return mIsRunning; }
    float getDeltaTime() { return deltaTime; }
    int getWindowHeight() { return WindowHeight; }
    int getWindowWidth() { return WindowWidth; }

    bool Initialize(string Name, int TLXCoordinate, int TPYCoordinate, int Width, int Height, int Flags, string FName);
    void Shutdown();
    void ProcessInput();
    void UpdateGame();
    void ClearRender();
    void GenerateOutput();
    void Write(char* NText, int TextW, int TextH, float TextX, float TextY);
    void Write(char* NText, int TextW, int TextH, float TextX, float TextY, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
    void DrawSimpleRect(float x, float y, int width, int height, int r, int g, int b, int alpha);
    void DrawRect(Position* P1, Position* P2, Position* P3, Position* P4, int r, int g, int b, int alpha);
    void DrawTriangle(Position* P1, Position* P2, Position* P3, int r, int g, int b, int alpha);
    void DrawLine(Position* P1, Position* P2, int r, int g, int b, int alpha);
    char CheckMovement();
    bool CheckPause();
    bool CheckReset();
    void FreeMemory();


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
