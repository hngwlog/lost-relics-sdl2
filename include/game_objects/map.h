#pragma once
#include "../init/defs.h"
#include "game_object.h"
#include "player.h"
#include "../animation/collision.h"
#include <fstream>
#include <vector>

const int GROUND_SIZE = 50;
const int CNT_BLOCK_X = SCREEN_WIDTH / GROUND_SIZE;
const int CNT_BLOCK_Y = SCREEN_HEIGHT / GROUND_SIZE;

class Map {
public:
    Map();
    ~Map();

    void loadMap(std::string path);
    void loadBackground(std::ifstream& mapFile);
    void loadPlayer(std::ifstream& mapFile);
    void loadGameObject(std::ifstream& mapFile);

    void checkAllCollision();
    void playerAndTiles();
    void playerAndCoins();
    void playerAndTraps();
    void playerAndStones();
    void stonesAndTiles();
    void buttonsAndStones();
    void playerAndWalls();
    void playerAndDoor();

    void update(const int& deltaTime);

    void render();

    int getState();

private:
    Map* chosenMap = nullptr;
    GameObject** tiles;

    Texture* healthMenuHud = nullptr;
    Texture* lifesIcon = nullptr;

    bool newCoinCollected = false;
    int coinsCollected = 0;
    Texture* coinHud = nullptr;
    Texture* coinsCount = nullptr;

    Player* player = nullptr;

    int totalCoins;
    std::vector<GameObject*> coins;

    int totalTraps;
    std::vector<GameObject*> traps;

    int totalWalls;
    std::vector<GameObject*> buttons;
    std::vector<GameObject*> stones;
    std::vector<GameObject*> walls;

    GameObject* door = nullptr;

    int state = 0;
};
