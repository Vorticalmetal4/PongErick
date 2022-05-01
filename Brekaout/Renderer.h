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

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    class SDL_Window* mWindow; // CPP: Puedes hacer mas general tu API de graficos con void*
    bool mIsRunning;
    class SDL_Renderer* mRenderer;
    float deltaTime;
    float mTicksCount;

};



