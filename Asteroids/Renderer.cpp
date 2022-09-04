// NOTE(isaveg): De la misma forma que Inih, Renderer es una clase que se esta duplicando en todos los proyectos. En la siguiente deberias convertirlo en una libreria 
//               y dejarlo fuera del proyecto.
//               con ese cambio el Input comienza a ser crucial tenerlo separado del Render pues cada juego tendra diferente Input, aunque el render siga utilizando todas las facilidades.
// 
// 
//               Alternativamente puedes solucionar el siguiente problema. 
//               Como podrias reutilizar el input  para subsiguientes juegos sin desacoplarlo sin cambiar nada de la clase render (es decir sin desacoplar Input de Render)?

#include "SDL2/include/SDL.h"  
#include "SDL2/include/SDL_ttf.h" 
#include "Renderer.h"
#include <string>



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
    mTicksCount(0)

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

// NOTE(isaveg): Renderer and Input are commonly  unrelated. How would you split them? HINT: do not use SDL for input processing
void Renderer::ProcessInput()
{
    SDL_Event event;
    // While there are still events in the queue
    while (SDL_PollEvent(&event))
    {
        // NOTE(isaveg): Missing keyboard/shortcut commands for debbuging and profiling during runtime. Frame rate, increase/decrease player speed, increase/decrease asteroids speed. Anything that helps debugging and testing during runtime
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


void Renderer::DrawSimpleRect(float x, float y, int width, int height, int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_Rect Rect{
    (int)x,
    (int)y,
    width,
    height
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
    // NOTE(isaveg): All input detection and states should be contained in the ProcessInput method
    if (State[SDL_SCANCODE_RIGHT])
        return 'R';
    else if (State[SDL_SCANCODE_LEFT])
        return 'L';
    else if (State[SDL_SCANCODE_UP])
        return 'U';
    else if (State[SDL_SCANCODE_SPACE])
        return 'S';

    return 'N';
}

bool Renderer::CheckPause()
{
    // NOTE(isaveg): All input detection and states should be contained in the ProcessInput method
    if (State[SDL_SCANCODE_P] && PauseCounter <= 0)
    {
        PauseCounter = 30;
        return true;
    }

    return false;
}

bool Renderer::CheckReset()
{
    // NOTE(isaveg): All input detection and states should be contained in the ProcessInput method
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


