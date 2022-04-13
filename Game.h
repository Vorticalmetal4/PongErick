#pragma once

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

    class SDL_Window* mWindow;
    bool mIsRunning;
    class SDL_Renderer* mRenderer;
    float deltaTime;
    float mTicksCount;

    class Stick* Player1;
    Stick* Player2;
    class Ball* GameBall;
    class Score* Sc;
};