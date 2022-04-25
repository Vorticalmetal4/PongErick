#include "Game.h"

// MODULARIDAD: Game.cpp puede ser tmb main, no es necesario que dejes a main en su propia clase por ahora. En las siguientes iteraciones de tu proyecto, estructuralo de forma que
// puedas reusar tanto como puedas

int main(int argc, char** argv) { // ESTILO: indentacion tipo JAVA, esta consciente que este estilo raramente se utiliza. Es mas comun una linea para el bracket, cuestion de gustos
    Game game;
    bool success = game.Initialize();

    if (success)
        game.RunLoop();

    game.Shutdown();

    return 0;

}