#include "../../include/game_objects/map.h"

Map::Map() {

    tiles = new GameObject* [CNT_BLOCK_Y];

    for (int i = 0; i < CNT_BLOCK_Y; i++) tiles[i] = new GameObject[CNT_BLOCK_X];
}

Map::~Map() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) delete[] tiles[i];
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

    mapFile.close();
}

void Map::update(const int& deltaTime) {


}

void Map::render() {

    for (int i = 0; i < CNT_BLOCK_Y; i++) {
        for (int j = 0; j < CNT_BLOCK_X; j++) {
            tiles[i][j].render();
        }
    }
}

int Map::getState() {

    return state;
}
