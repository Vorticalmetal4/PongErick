#pragma once // CPP: duplicado

#pragma once

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game(void);
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

    class Stick* Player1; // MODULARIDAD: Realmente un stick no es un jugador. Mas bien un Player puede tener un input.
    Stick* Player2;
    class Ball* GameBall;
    class Score* Sc;
};