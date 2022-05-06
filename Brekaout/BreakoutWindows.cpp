#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"


int main(int argc, int **argv){
    Renderer render;
    bool success = render.Initialize();
    Player* Player1 = new Player(&render);

    if (success) {
        while (render.getmIsRunning()) {
            render.ProcessInput();
            render.UpdateGame();
            render.ClearRender();
            Player1->Update();
            render.GenerateOutput();
        }
    }
        

    render.Shutdown();

    return 0;
}

