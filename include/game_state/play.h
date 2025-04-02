#pragma once
#include "../init/graphics.h"
#include "../game_objects/map.h"

class Game {
public:
    Game();
    ~Game();

    void init(int level);

    void update(const int& deltaTime);

    void render();

    void renderPause();

    void renderLose();

    void renderWin();

    int getGameState();

private:
    Map* chosenMap = nullptr;

    Texture* background = nullptr;

    Texture* pause = nullptr;

    Texture* lose = nullptr;

    Texture* win = nullptr;

    Texture* quit = nullptr;

    int state = 0;
};
