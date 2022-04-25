#include "./SDL2/include/SDL.h"
#include "Game.h"
#include "Stick.h"
#include "Ball.h"
#include "Score.h"



const int thickness = 15;
const int WindowHeight = 700;
const int WindowWidth = 1024;


Game::Game(void)
    :mWindow(nullptr)
    , mIsRunning(true)
    , mRenderer(NULL)
{

}

bool Game::Initialize() {

    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(
        "Game Programming in C++ (Chapter 1)", // Window title
        100, // Top left x-coordinate of window
        20, // Top left y-coordinate of window
        WindowWidth, // Width of window
        WindowHeight, // Height of window
        0 // Flags (0 for no flags set)
    );

    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GameBall = new Ball(WindowWidth / 2, WindowHeight / 2, 150, 150, thickness);

    Player1 = new Stick(200, 300, thickness * 4, 400, thickness); // CPP: Memory leak
    Player2 = new Stick(824, 300, thickness * 4, 400, thickness); // CPP: Memory leak

    Sc = new Score(); // CPP: Memory leak


    return true;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    // CPP: Always nullify pointer, or you can get Invalid memory reference, etc.
    // mWindow = nullptr;
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    // While there are still events in the queue
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
        mIsRunning = false;
    else {
        if (state[SDL_SCANCODE_W])
            if (Player1->CheckBorders(Player1->getVelocity() * -deltaTime, 0, WindowHeight))
                Player1->MoveYPosition(static_cast<int>(Player1->getVelocity() * -deltaTime));

        if (state[SDL_SCANCODE_S])
            if (Player1->CheckBorders(Player1->getVelocity() * deltaTime, 0, WindowHeight))
                Player1->MoveYPosition(static_cast<int>(Player1->getVelocity() * deltaTime));

        if (state[SDL_SCANCODE_UP])
            if (Player2->CheckBorders(Player2->getVelocity() * -deltaTime, 0, WindowHeight))
                Player2->MoveYPosition(static_cast<int>(Player2->getVelocity() * -deltaTime));
        if (state[SDL_SCANCODE_DOWN])
            if (Player2->CheckBorders(Player2->getVelocity() * deltaTime, 0, WindowHeight))
                Player2->MoveYPosition(static_cast<int>(Player2->getVelocity() * deltaTime));
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    mTicksCount = SDL_GetTicks();



    if (GameBall->getXPosition() < WindowWidth / 2) {       //Checking if the side of the ball
        if (!Player1->CollitionWBall(GameBall, 1))      //Checking if one of the players hited the ball
            GameBall->WallCollition(WindowHeight, WindowWidth, Sc);     //Checking if the ball hited one of the walls
    }
    else {
        if (!Player2->CollitionWBall(GameBall, 2))
            GameBall->WallCollition(WindowHeight, WindowWidth, Sc);
    }

    GameBall->Move(static_cast<int>(GameBall->getXVelocity() * deltaTime), static_cast<int>(GameBall->getYVelocity() * deltaTime));
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    //Clearing the buffer
    SDL_RenderClear(mRenderer);


    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    SDL_Rect CenterLine{
        WindowWidth / 2 - thickness / 2,
        0,
        thickness,
        WindowHeight,
    };

    SDL_RenderFillRect(mRenderer, &CenterLine);


    ////////////////////////////////Drawing de Players

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);

    // MODULARIDAD: Player or any other actor in the game should render themselves, also this way you are not using CACHE memory in a smart way
    SDL_Rect PlayerOne{
        Player1->getXPosition(), //X top left
        Player1->getYPosition(), //Y top left
        thickness, //Width
        Player1->getHeight() //Height
    };

    SDL_RenderFillRect(mRenderer, &PlayerOne);

    SDL_Rect PlayerTwo{
        Player2->getXPosition(),
        Player2->getYPosition(),
        thickness,
        Player2->getHeight()
    };

    SDL_RenderFillRect(mRenderer, &PlayerTwo);



    //////////////////////////////////////////////////////////////// Drawing the numbers

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // CPP: S1 to SN seems should be a table stored statically
    SDL_Rect S1{
        300,
        50,
        thickness * 4,
        thickness
    };

    SDL_Rect S2{
        300,
        50 + thickness,
        thickness,
        thickness * 3
    };

    SDL_Rect S3{
        300,
        50 + thickness * 3,
        thickness * 4,
        thickness
    };

    SDL_Rect S4{
        300,
        50 + thickness * 4,
        thickness,
        thickness * 2
    };

    SDL_Rect S5{
        300,
        50 + thickness * 6,
        thickness * 4,
        thickness
    };

    SDL_Rect S6{
        345,
        50 + thickness * 4,
        thickness,
        thickness * 2
    };

    SDL_Rect S7{
        345,
        50 + thickness,
        thickness,
        thickness * 3,
    };

    SDL_Rect S8{
        684,
        50,
        thickness * 4,
        thickness
    };

    SDL_Rect S9{
        684,
        50 + thickness,
        thickness,
        thickness * 3
    };

    SDL_Rect S10{
        684,
        50 + thickness * 3,
        thickness * 4,
        thickness
    };

    SDL_Rect S11{
        684,
        50 + thickness * 4,
        thickness,
        thickness * 2
    };

    SDL_Rect S12{
        684,
        50 + thickness * 6,
        thickness * 4,
        thickness
    };

    SDL_Rect S13{
        729,
        50 + thickness * 4,
        thickness,
        thickness * 2
    };

    SDL_Rect S14{
        729,
        50 + thickness,
        thickness,
        thickness * 3,
    };

    switch (Sc->getPlayer1Score()) {
    case 0:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S4);
        SDL_RenderFillRect(mRenderer, &S5);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;

    case 1:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;

    case 2:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S7);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S4);
        SDL_RenderFillRect(mRenderer, &S5);
        break;

    case 3:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S5);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;

    case 4:
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;

    case 5:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S5);
        break;

    case 6:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S4);
        SDL_RenderFillRect(mRenderer, &S5);
        SDL_RenderFillRect(mRenderer, &S6);
        break;

    case 7:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S7);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S6);
        break;

    case 8:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S4);
        SDL_RenderFillRect(mRenderer, &S5);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;

    case 9:
        SDL_RenderFillRect(mRenderer, &S1);
        SDL_RenderFillRect(mRenderer, &S2);
        SDL_RenderFillRect(mRenderer, &S3);
        SDL_RenderFillRect(mRenderer, &S5);
        SDL_RenderFillRect(mRenderer, &S6);
        SDL_RenderFillRect(mRenderer, &S7);
        break;
    }

    // CPP: Duplicated code, NO!
    switch (Sc->getPlayer2Score()) {
    case 0:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S11);
        SDL_RenderFillRect(mRenderer, &S12);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;

    case 1:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;

    case 2:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S14);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S11);
        SDL_RenderFillRect(mRenderer, &S12);
        break;

    case 3:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S12);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;

    case 4:
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;

    case 5:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S12);
        break;

    case 6:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S11);
        SDL_RenderFillRect(mRenderer, &S12);
        SDL_RenderFillRect(mRenderer, &S13);
        break;

    case 7:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S14);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S13);
        break;

    case 8:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S11);
        SDL_RenderFillRect(mRenderer, &S12);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;

    case 9:
        SDL_RenderFillRect(mRenderer, &S8);
        SDL_RenderFillRect(mRenderer, &S9);
        SDL_RenderFillRect(mRenderer, &S10);
        SDL_RenderFillRect(mRenderer, &S12);
        SDL_RenderFillRect(mRenderer, &S13);
        SDL_RenderFillRect(mRenderer, &S14);
        break;
    }

    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

    ////////Drawing the ball

    // MODULARITY: Ball should render itself
    SDL_Rect GBall{
        GameBall->getXPosition(),
        GameBall->getYPosition(),
        thickness,
        thickness
    };

    SDL_RenderFillRect(mRenderer, &GBall);

    //Drawing the screen
    SDL_RenderPresent(mRenderer);
}