#include "../SDL2/include/SDL.h"  // nunca uses paths relativos cuando incluyas archivos debe  ser  #include "SDL2/include/SDL.h"
#include "../SDL2/include/SDL_ttf.h" // nunca uses paths relativos cuando incluyas archivos debe ser  #include "SDL2/include/SDL_ttf.h"
#include "Renderer.h"

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
        "Breakout", // Window title // deberia pasarse como parametro en initialize
        100, // Top left x-coordinate of window // deberia pasarse como parametro en initialize
        20, // Top left y-coordinate of window // deberia pasarse como parametro en initialize
        WindowWidth, // Width of window // deberia pasarse como parametro en initialize
        WindowHeight, // Height of window // deberia pasarse como parametro en initialize
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
    
}

void Renderer::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    mTicksCount = SDL_GetTicks();


}

void Renderer::ClearRender() {
    SDL_RenderClear(mRenderer);
}

void Renderer::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    //Clearing the buffer

    SDL_RenderPresent(mRenderer);
}


void Renderer::DrawRect(int x, int y, float width, float height, int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(mRenderer, r, g, b, alpha);
    SDL_Rect Rect{
    x,
    y,
    width,
    height
    };

    SDL_RenderFillRect(mRenderer, &Rect);
}

void Renderer::Write(char* NText, int TextW, int TextH, int TextX, int TextY) {

    TTF_Init();
    TTF_Font* Font = TTF_OpenFont("ArialCE.ttf", 25); // string que debe configurarse en el config ini
    SDL_Color TextColor = { 255, 255, 255 , 255};
    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, NText, TextColor);
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(mRenderer, TextSurface);
    SDL_QueryTexture(Texture, NULL, NULL, &TextW, &TextH);
    SDL_Rect TextRect = {TextX, TextY, TextW, TextH};
    SDL_RenderCopy(mRenderer, Texture, NULL, &TextRect);

    TTF_CloseFont(Font);
    SDL_DestroyTexture(Texture);
    SDL_FreeSurface(TextSurface);
    TTF_Quit();

}