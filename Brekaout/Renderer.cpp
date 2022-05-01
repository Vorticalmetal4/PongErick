#include "../SDL2/include/SDL.h"
#include "Renderer.h"


const int thickness = 15;
const int WindowHeight = 700;
const int WindowWidth = 1024;

Renderer::Renderer(void)
    :mWindow(nullptr)
    , mIsRunning(true)
    , mRenderer(NULL)
{

}

bool Renderer::Initialize() {

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


    return true;
}

void Renderer::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Renderer::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;
    SDL_Quit();
}

void Renderer::ProcessInput() {

}

void Renderer::UpdateGame() {

}

void Renderer::GenerateOutput() {

}
