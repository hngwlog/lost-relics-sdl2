#include "../../include/game_objects/map.h"

void Map::loadMap(std::string path) {

    std::ifstream mapFile(path.c_str());
    if (mapFile.fail()) logErrorAndExit("Could not load map!", "Map.cpp");

    loadBackground(mapFile);
    loadPlayer(mapFile);
    loadGameObject(mapFile);

    mapFile.close();
}

void Map::loadBackground(std::ifstream& mapFile) {

    std::string tmp = "assets/images/tiles/";
    for (int i = 0; i < CNT_BLOCK_Y; i++) {
        for (int j = 0; j < CNT_BLOCK_X; j++) {
            int type = 0;
            mapFile >> type;
            if (!type) continue;
            std::string typeTile = tmp + std::to_string(type) + ".png";
            tiles[i][j].init(typeTile, {GROUND_SIZE, GROUND_SIZE}, {j * GROUND_SIZE, i * GROUND_SIZE}, {1, 1}, {{1, 0}});
        }
    }

    healthMenuHud = new Texture();
    healthMenuHud->loadFromFile("assets/images/hud/health_menu_hud.png");
    healthMenuHud->setSize({225, 75});
    healthMenuHud->setPosition({10, 10});

    lifesIcon = new Texture();
    lifesIcon->loadFromFile("assets/images/hud/lifes_icon.png");
    lifesIcon->setSize({40, 40});
    lifesIcon->setPosition({28, 25});

    coinHud = new Texture();
    coinHud->loadFromFile("assets/images/hud/coins_hud.png");
    coinHud->setSize({30, 30});
    coinHud->setPosition({920, 20});

    std::string fontPath = "assets/fonts/brownie_stencil.ttf";
    gFont = TTF_OpenFont(fontPath.c_str(), 20);

    coinsCount = new Texture();
    std::string label = "x" + std::to_string(coinsCollected);
    coinsCount->loadFromText(label, {255, 255, 0});
    coinsCount->setPosition({coinHud->getPosition().first + coinHud->getWidth(), coinHud->getPosition().second});

}

void Map::loadPlayer(std::ifstream& mapFile) {

    std::pair<int, int> playerStartPosition;
    bool playerFacingRight;

    mapFile >> playerStartPosition.first >> playerStartPosition.second >> playerFacingRight;
    player = new Player(playerStartPosition, playerFacingRight);
}

void Map::loadGameObject(std::ifstream& mapFile) {

    mapFile >> totalCoins;
    for (int i = 0; i < totalCoins; i++) {
        GameObject* coin = new GameObject();
        int x, y;
        mapFile >> x >> y;
        coin->init("assets/images/game_objects/coin_idle.png", {25, 25}, {x, y}, {6, 1}, {{6, 0}});
        coins.push_back(coin);
    }

    mapFile >> totalTraps;
    for (int i = 0; i < totalTraps; i++) {
        GameObject* trap = new GameObject();
        int x, y, type;
        mapFile >> x >> y >> type;
        if (type) trap->init("assets/images/game_objects/spike_top.png", {50, 50}, {x, y}, {7, 1}, {{7, 0}});
        else trap->init("assets/images/game_objects/spike_down.png", {50, 50}, {x, y}, {7, 1}, {{7, 0}});
        trap->setDelayTime(1000);
        traps.push_back(trap);
    }

    mapFile >> totalWalls;
    for (int i = 0; i < totalWalls; i++) {
        int x, y;

        mapFile >> x >> y;
        GameObject* button = new GameObject();
        button->init("assets/images/game_objects/button.png", {50, 12}, {x, y}, {2, 1}, {{2, 0}});
        buttons.push_back(button);

        mapFile >> x >> y;
        GameObject* stone = new GameObject();
        stone->init("assets/images/game_objects/stone.png", {50, 50}, {x, y}, {1, 1}, {{1, 0}});
        stones.push_back(stone);

        mapFile >> x >> y;
        GameObject* wall = new GameObject();
        wall->init("assets/images/game_objects/wall.png", {50, 150}, {x, y}, {14, 2}, {{10, 0}, {14, 1}});
        walls.push_back(wall);
    }

    int x, y;
    mapFile >> x >> y;
    door = new GameObject();
    door->init("assets/images/game_objects/door.png", {60, 80}, {x, y}, {1, 1}, {{1, 0}});
}
