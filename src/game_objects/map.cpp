#include "../../include/game_objects/map.h"

Map::Map() {

    tiles = new GameObject* [CNT_BLOCK_Y];

    for (int i = 0; i < CNT_BLOCK_Y; i++) tiles[i] = new GameObject[CNT_BLOCK_X];
}

Map::~Map() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) delete[] tiles[i];
    delete healthMenuHud;
    delete lifesIcon;
    delete player;
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

    std::pair<int, int> playerStartPosition;
    bool playerFacingRight;

    mapFile >> playerStartPosition.first >> playerStartPosition.second >> playerFacingRight;
    player = new Player(playerStartPosition, playerFacingRight);

    mapFile.close();
}

void Map::update(const int& deltaTime) {

    checkAllCollision();
    player->update(deltaTime);
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
}

void Map::render() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) {
        for (int j = 0; j < CNT_BLOCK_X; j++) {
            tiles[i][j].render();
        }
    }

    healthMenuHud->render();
    lifesIcon->render();

    player->render();
}

int Map::getState() {

    return state;
}
