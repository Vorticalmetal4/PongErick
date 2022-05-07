#include "BreakoutWindows.h"
#include "Renderer.h"
#include "Player.h"
#include "Ball.h"


int main(int argc, int **argv){
    Renderer Rend;
    bool success = Rend.Initialize();
    Player* Player1 = new Player(&Rend);
    Ball* MainBall = new Ball(&Rend, Player1);

    if (success) {
        while (Rend.getmIsRunning()) {
            Rend.ProcessInput();
            Rend.UpdateGame();
            Rend.ClearRender();
            MainBall->Update();
            Player1->Update();
            Rend.GenerateOutput();
        }
    }
        

    Rend.Shutdown();

    return 0;
}

