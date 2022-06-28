#include "SDL2/include/SDL.h"  
#include "SDL2/include/SDL_ttf.h" 
#include "Renderer.h"
#include <string>
#include <iostream>

using namespace std;

const Uint8* State = SDL_GetKeyboardState(NULL);
TTF_Font* Font;

Renderer::Renderer(void)
    :mWindow(nullptr),
    mIsRunning(true),
    mRenderer(NULL),
    PauseCounter(0),
    WindowHeight(0),
    WindowWidth(0),
    FText(nullptr),
    TextSurface(nullptr),
    Texture(nullptr)
{

}

bool Renderer::Initialize(string Name, int TLXCoordinate, int TLYCoordinate, int Width, int Height, int Flags, string FName)
{

    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    char* WNText = (char*)malloc((Name.size() + 1) * sizeof(char));
    Name.copy(WNText, Name.size() + 1);
    WNText[Name.size()] = '\0';

    mWindow = SDL_CreateWindow(
        WNText, // Window title // deberia pasarse como parametro en initialize
        TLXCoordinate, // Top left x-coordinate of window // deberia pasarse como parametro en initialize
        TLYCoordinate, // Top left y-coordinate of window // deberia pasarse como parametro en initialize
        Width, // Width of window // deberia pasarse como parametro en initialize
        Height, // Height of window // deberia pasarse como parametro en initialize
        Flags // Flags (0 for no flags set)
    );

    WindowHeight = Height;
    WindowWidth = Width;

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    free(WNText);
    FontName = FName;

    TTF_Init();

    FText = (char*)malloc((FontName.size() + 1) * sizeof(char));
    FontName.copy(FText, FontName.size() + 1);
    FText[FontName.size()] = '\0';

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return true;
}

void Renderer::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;
    SDL_Quit();
}

void Renderer::ProcessInput()
{
    SDL_Event event;
    // While there are still events in the queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
        mIsRunning = false;

}

void Renderer::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    mTicksCount = SDL_GetTicks();
    PauseCounter--;


}

void Renderer::ClearRender()
{
    SDL_RenderClear(mRenderer);
}

void Renderer::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    //Clearing the buffer

    SDL_RenderPresent(mRenderer);
}


void Renderer::DrawRect(int x, int y, float width, float height, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_Rect Rect{
    x,
    y,
    width,
    height
    };

    SDL_RenderFillRect(mRenderer, &Rect);

}

void Renderer::Write(char* NText, int TextW, int TextH, int TextX, int TextY)
{

    Font = TTF_OpenFont(FText, 25);
    TextSurface = TTF_RenderText_Solid(Font, NText, { 255, 255, 255, 255 });
    Texture = SDL_CreateTextureFromSurface(mRenderer, TextSurface); // isaveg: verify, do you really need to create and destroy every frame?
    SDL_QueryTexture(Texture, NULL, NULL, &TextW, &TextH);
    SDL_Rect TextRect = { TextX, TextY, TextW, TextH };
    SDL_RenderCopy(mRenderer, Texture, NULL, &TextRect);

    TTF_CloseFont(Font);
    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(Texture);

}

char Renderer::CheckMovement()
{
    if (State[SDL_SCANCODE_RIGHT])
        return 'R';
    else if (State[SDL_SCANCODE_LEFT])
        return 'L';
    else if (State[SDL_SCANCODE_UP])
        return 'U';
    else if (State[SDL_SCANCODE_SPACE])
        return 'P';

    return 'N';
}

bool Renderer::CheckPause()
{
    if (State[SDL_SCANCODE_P] && PauseCounter <= 0)
    {
        PauseCounter = 30;
        return true;
    }

    return false;
}

void Renderer::FreeMemory()
{
    free(FText);
    FText = nullptr; // always nullify when  freeing memory
    TTF_Quit();
}

void Renderer::DrawTriangle(int P1x, int P1y, int P2x, int P2y, int P3x, int P3y, int r, int g, int b, int alpha)
{

    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_RenderDrawLine(mRenderer, P1x, P1y, P2x, P2y);
    SDL_RenderDrawLine(mRenderer, P1x, P1y, P3x, P3y);
    SDL_RenderDrawLine(mRenderer, P2x, P2y, P3x, P3y);
}