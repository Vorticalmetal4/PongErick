#pragma once

struct Vector2 {
    float x;
    float y;
};

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

    bool getmIsRunning() { return mIsRunning; }
    float getDeltaTime() { return deltaTime; }
    int getWindowHeight() { return WindowHeight; }
    int getWindowWidth() { return WindowWidth; }
    void DrawRect(int x, int y, float width, float height);

private:

    class SDL_Window* mWindow; // CPP: Puedes hacer mas general tu API de graficos con void*
    bool mIsRunning;
    class SDL_Renderer* mRenderer;
    float deltaTime;
    float mTicksCount;
    const int WindowHeight = 700;
    const int WindowWidth = 1024;

};



