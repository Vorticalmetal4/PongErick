#include "BreakoutWindows.h"
#include "Renderer.h"


int main(int argc, int **argv){
    Renderer game;
    bool success = game.Initialize();

    if (success)
        game.RunLoop();

    game.Shutdown();

    return 0;
}