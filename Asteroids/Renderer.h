#pragma once

#pragma once 
#pragma once 

#include <string>
using namespace std;

struct Position
{
    double x;
    double y;
    int Angle;
    double Rotation;
};

class Renderer
{
public:
    Renderer(void);
    bool Initialize(string Name, int TLXCoordinate, int TPYCoordinate, int Width, int Height, int Flags, string FName);
    void Shutdown();
    void ProcessInput();
    void UpdateGame();
    void ClearRender();
    void GenerateOutput();
    void Write(char* NText, int TextW, int TextH, int TextX, int TextY);

    bool getIsRunning() { return mIsRunning; }
    float getDeltaTime() { return deltaTime; }
    int getWindowHeight() { return WindowHeight; }
    int getWindowWidth() { return WindowWidth; }
    void DrawSimpleRect(int x, int y, float width, float height, int r, int g, int b, int alpha);
    void DrawRect(Position* P1, Position* P2, Position* P3, Position* P4, int r, int g, int b, int alpha);
    void DrawTriangle(Position* P1, Position* P2, Position* P3, int r, int g, int b, int alpha);
    char CheckMovement();
    bool CheckPause();
    void FreeMemory();


private:

    class SDL_Window* mWindow; 
    bool mIsRunning;
    class SDL_Renderer* mRenderer;
    float deltaTime = 0;
    float mTicksCount = 0;
    int WindowHeight;
    int WindowWidth;
    string FontName;
    char* FText;
    int PauseCounter;

    class SDL_Surface* TextSurface;
    class SDL_Texture* Texture;

};
