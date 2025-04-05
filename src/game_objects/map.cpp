#include "../../include/game_objects/map.h"

Map::Map() {

    tiles = new GameObject* [CNT_BLOCK_Y];

    for (int i = 0; i < CNT_BLOCK_Y; i++) tiles[i] = new GameObject[CNT_BLOCK_X];
}

Map::~Map() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) delete[] tiles[i];
    delete[] tiles;
    delete healthMenuHud;
    delete lifesIcon;
    delete coinHud;
    delete coinsCount;
    delete player;
    for (auto& coin: coins) delete coin;
}

void Map::loadMap(std::string path) {

    std::ifstream mapFile(path.c_str());
    if (mapFile.fail()) logErrorAndExit("Could not load map!", "Map.cpp");

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

    std::pair<int, int> playerStartPosition;
    bool playerFacingRight;

    mapFile >> playerStartPosition.first >> playerStartPosition.second >> playerFacingRight;
    player = new Player(playerStartPosition, playerFacingRight);

    mapFile >> totalCoins;
    for (int i = 0; i < totalCoins; i++) {
        GameObject* coin = new GameObject();
        int x, y;
        mapFile >> x >> y;
        coin->init("assets/images/game_objects/coin_idle.png", {25, 25}, {x, y}, {6, 1}, {{6, 0}});
        coins.push_back(coin);
    }

    mapFile.close();
}

void Map::update(const int& deltaTime) {

    checkAllCollision();
    player->update(deltaTime);
    for (auto& coin: coins) coin->update(deltaTime);
}

void Map::checkAllCollision() {

    player->isGrounded = false;
    player->isHeadBlocked = false;

    for (int i = 0; i < CNT_BLOCK_Y; i++) {
        for (int j = 0; j < CNT_BLOCK_X; j++) {
            if (tiles[i][j].getBox() == nullptr) continue;
            int state = tiles[i][j].getBox()->check(player->getBox(), true);
            if (state == COLLISION_STATE::DOWN) player->isHeadBlocked = true;
            else if (state == COLLISION_STATE::TOP || state == COLLISION_STATE::MTOP) player->isGrounded = true;
        }
    }

    newCoinCollected = false;
    for (auto& coin: coins) {
        if (coin->isChecked) continue;
        if (player->getBox()->check(coin->getBox(), false) != COLLISION_STATE::NONE) {
            newCoinCollected = true;
            coinsCollected++;
            coin->isChecked = true;
            std::pair<int, int> objPosition = coin->getPosition();
            coin->init("assets/images/game_objects/coin_pick_up.png", {25, 50}, {objPosition.first, objPosition.second - 25}, {6, 1}, {{6, 0}});
        }
    }
}

void Map::render() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) {
        for (int j = 0; j < CNT_BLOCK_X; j++) {
            tiles[i][j].render();
        }
    }

    player->render();

    for (auto& coin: coins) coin->render();

    healthMenuHud->render();
    lifesIcon->render();

    coinHud->render();

    if (newCoinCollected) {
        std::string path = "assets/fonts/brownie_stencil.ttf";
        gFont = TTF_OpenFont(path.c_str(), 20);

        std::string label = "x" + std::to_string(coinsCollected);
        coinsCount->loadFromText(label, {255, 255, 0});
        coinsCount->setPosition({coinHud->getPosition().first + coinHud->getWidth(), coinHud->getPosition().second});
    }

    coinsCount->render();
}

int Map::getState() {

    return state;
}
