#include "include/init/defs.h"
#include "include/init/graphics.h"
#include "include/game_state/manager.h"

int main(int argc, char* argv[]) {

    initSDL();
    initMusic();
    int type = HOME;
    while (type != - 1) {
        if (type == HOME) type = loadHomeScreen();
        else if (type == START) type = loadGame();
        else if (type == INSTRUCTION) type = loadInstruction();
        else if (type == OPTIONS) type = loadOptions();
        else type = loadQuit();
    }
    return 0;
}
