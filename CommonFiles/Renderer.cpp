#include "SDL2/include/SDL.h"  
#include "SDL2/include/SDL_ttf.h" 
#include "Renderer.h"
#include <string>

const float Pi = (float)3.141592;
const float Rad = Pi / 180;
int i;

const Uint8* State = SDL_GetKeyboardState(NULL);
TTF_Font* Font = nullptr;
SDL_Rect TextRect;
SDL_Window* mWindow = nullptr;
SDL_Surface* TextSurface = nullptr;
SDL_Texture* Texture = nullptr;
SDL_Renderer* mRenderer = nullptr;

Renderer::Renderer(void)
    :mIsRunning(true),
    PauseCounter(0),
    WindowHeight(0),
    WindowWidth(0),
    FText(nullptr),
    deltaTime(0),
    mTicksCount(0),
    HWidth(0),
    HHeight(0)
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
    if (WNText != NULL)
    {
        Name.copy(WNText, Name.size() + 1);
        WNText[Name.size()] = '\0';
    }

    mWindow = SDL_CreateWindow(
        WNText,
        TLXCoordinate,
        TLYCoordinate,
        Width,
        Height,
        Flags
    );

    WindowHeight = Height;
    WindowWidth = Width;
    HWidth = Width / 2.0f;
    HHeight = Height / 2.0f;

    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    free(WNText);
    FontName = FName;

    TTF_Init();

    FText = (char*)malloc((FontName.size() + 1) * sizeof(char));
    if (FText != NULL)
    {
        FontName.copy(FText, FontName.size() + 1);
        FText[FontName.size()] = '\0';
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Font = TTF_OpenFont(FText, 25);


    for (i = 0; i  < 360; i++)
    {
        X[i] = cosf(i * Rad);
        Y[i] = sinf(i * Rad);
    }

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
    mTicksCount = (float)SDL_GetTicks();
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


void Renderer::DrawSimpleRect(Position* ActualPosition, Dimension* Dimensions, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_Rect Rect{
    (int)ActualPosition->x,
    (int)ActualPosition->y,
    (int)Dimensions->Width,
    (int)Dimensions->Height
    };

    SDL_RenderFillRect(mRenderer, &Rect);

}

void Renderer::Write(char* NText, int TextW, int TextH, float TextX, float TextY)
{
    TextSurface = TTF_RenderText_Solid(Font, NText, { 255, 255, 255, 255 });
    Texture = SDL_CreateTextureFromSurface(mRenderer, TextSurface);  // isaveg: verify, do you really need to create and destroy every frame?
    SDL_QueryTexture(Texture, NULL, NULL, &TextW, &TextH);
    TextRect = { (int)TextX, (int)TextY, TextW, TextH };

    SDL_RenderCopy(mRenderer, Texture, NULL, &TextRect);

    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(Texture);

}

void Renderer::Write(char* NText, int TextW, int TextH, float TextX, float TextY, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
    TextSurface = TTF_RenderText_Solid(Font, NText, { r, g, b, alpha });
    Texture = SDL_CreateTextureFromSurface(mRenderer, TextSurface);
    SDL_QueryTexture(Texture, NULL, NULL, &TextW, &TextH);
    TextRect = { (int)TextX, (int)TextY, TextW, TextH };

    SDL_RenderCopy(mRenderer, Texture, NULL, &TextRect);

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
    else if (State[SDL_SCANCODE_DOWN])
        return 'D';
    else if (State[SDL_SCANCODE_SPACE])
        return 'S';

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

bool Renderer::CheckReset()
{
    if (State[SDL_SCANCODE_R])
        return true;

    return false;
}

void Renderer::FreeMemory()
{
    free(FText);
    FText = nullptr;
    TTF_CloseFont(Font);
    Font = nullptr;
    TTF_Quit();
}

void Renderer::DrawTriangle(Position* P1, Position* P2, Position* P3, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_RenderDrawLineF(mRenderer, P1->x, P1->y, P2->x, P2->y);
    SDL_RenderDrawLineF(mRenderer, P1->x, P1->y, P3->x, P3->y);
    SDL_RenderDrawLineF(mRenderer, P2->x, P2->y, P3->x, P3->y);
}

void Renderer::DrawRect(Position* P1, Position* P2, Position* P3, Position* P4, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_RenderDrawLineF(mRenderer, P1->x, P1->y, P2->x, P2->y);
    SDL_RenderDrawLineF(mRenderer, P2->x, P2->y, P3->x, P3->y);
    SDL_RenderDrawLineF(mRenderer, P3->x, P3->y, P4->x, P4->y);
    SDL_RenderDrawLineF(mRenderer, P4->x, P4->y, P1->x, P1->y);

}

void Renderer::DrawLine(Position* P1, Position* P2, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_RenderDrawLineF(mRenderer, P1->x, P1->y, P2->x, P2->y);
}

void Renderer::DrawIncompleteCircle(Position* Center, float Radius, int r, int g, int b, int alpha, float FirstSpaceAngle, float SecondSpaceAngle) {
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);

    for (i = 0; i < 360; i ++)
    {
        if (Center->Angle > 0)
        {
            if (i < FirstSpaceAngle || i > SecondSpaceAngle)
                SDL_RenderDrawLineF(mRenderer, Center->x, Center->y, Center->x + X[i] * Radius, Center->y - Y[i] * Radius);
        }
        else
            if(i > FirstSpaceAngle && i < SecondSpaceAngle)
                SDL_RenderDrawLineF(mRenderer, Center->x, Center->y, Center->x + X[i] * Radius, Center->y - Y[i] * Radius);
    }

}

void Renderer::DrawCircle(Position* Center, float Radius, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    for (i = 0; i < 360; i++)
        SDL_RenderDrawLineF(mRenderer, Center->x, Center->y, Center->x + X[i] * Radius, Center->y - Y[i] * Radius);
}