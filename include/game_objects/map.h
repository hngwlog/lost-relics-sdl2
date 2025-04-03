#pragma once
#include "../init/defs.h"
#include "game_object.h"
#include "player.h"
#include "../animation/collision.h"
#include <fstream>

const int GROUND_SIZE = 50;
const int CNT_BLOCK_X = SCREEN_WIDTH / GROUND_SIZE;
const int CNT_BLOCK_Y = SCREEN_HEIGHT / GROUND_SIZE;

class Map {
public:
    Map();
    ~Map();

    void loadMap(std::string path);

    void update(const int& deltaTime);

    void checkAllCollision();

    void render();

    int getState();

private:
    Map* chosenMap = nullptr;
    GameObject** tiles;

    Texture* healthMenuHud = nullptr;
    Texture* lifesIcon = nullptr;

    Player* player = nullptr;

    int state = 0;
};
