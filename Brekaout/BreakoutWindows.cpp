#include "BreakoutWindows.h"
#include "Renderer.h"


int main(int argc, int **argv){
    Renderer render;
    bool success = render.Initialize();

    if (success) {
        while (render.getmIsRunning()) {
            render.ProcessInput();
            render.UpdateGame();
            render.GenerateOutput();
        }
    }
        

    render.Shutdown();

    return 0;
}

