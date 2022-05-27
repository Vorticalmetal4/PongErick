#pragma once 

class Renderer {
public:
    Renderer(void);
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void ProcessInput();
    void UpdateGame();
    void ClearRender();
    void GenerateOutput();
    void Write(char* NText, int TextW, int TextH, int TextX, int TextY);

    bool getmIsRunning() { return mIsRunning; }
    float getDeltaTime() { return deltaTime; }
    int getWindowHeight() { return WindowHeight; }
    int getWindowWidth() { return WindowWidth; }
    void DrawRect(int x, int y, float width, float height, int r, int g, int b, int alpha);

private:

    class SDL_Window* mWindow; // CPP: Puedes hacer mas general tu API de graficos con void*
    bool mIsRunning;
    class SDL_Renderer* mRenderer;
    float deltaTime = 0;
    float mTicksCount  = 0;
    const int WindowHeight = 700;
    const int WindowWidth = 1024;

};



