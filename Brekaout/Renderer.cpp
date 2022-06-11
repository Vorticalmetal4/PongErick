#include "../SDL2/include/SDL.h"  // nunca uses paths relativos cuando incluyas archivos debe  ser  #include "SDL2/include/SDL.h"
#include "../SDL2/include/SDL_ttf.h" // nunca uses paths relativos cuando incluyas archivos debe ser  #include "SDL2/include/SDL_ttf.h"
#include "Renderer.h"
#include <string>
#include <iostream>

using namespace std;

const Uint8* State = SDL_GetKeyboardState(NULL);


Renderer::Renderer(void)
    :mWindow(nullptr)
    , mIsRunning(true)
    , mRenderer(NULL)
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

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return true;
}

void Renderer::RunLoop()
{
    while (mIsRunning)
    {
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

    TTF_Init();
    FText = (char*)malloc((FontName.size() + 1) * sizeof(char));
    FontName.copy(FText, FontName.size() + 1);
    FText[FontName.size()] = '\0';

    TTF_Font* Font = TTF_OpenFont(FText, 25);
    SDL_Color TextColor = { 255, 255, 255 , 255};
    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, NText, TextColor);
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(mRenderer, TextSurface);
    SDL_QueryTexture(Texture, NULL, NULL, &TextW, &TextH);
    SDL_Rect TextRect = {TextX, TextY, TextW, TextH};
    SDL_RenderCopy(mRenderer, Texture, NULL, &TextRect);

    free(FText);
    TTF_CloseFont(Font);
    SDL_DestroyTexture(Texture);
    SDL_FreeSurface(TextSurface);
    TTF_Quit();

}

char Renderer::CheckMovement() 
{
    if (State[SDL_SCANCODE_RIGHT])
        return 'R';
    else if (State[SDL_SCANCODE_LEFT])
        return 'L';
    else if (State[SDL_SCANCODE_SPACE])
        return 'P';
}