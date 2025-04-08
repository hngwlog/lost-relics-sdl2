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
    for (auto& trap: traps) delete trap;
    for (auto& button: buttons) delete button;
    for (auto& stone: stones) delete stone;
    for (auto& wall: walls) delete wall;
    delete door;
    for (auto& enemy: enemies) delete enemy;
}

void Map::update(const int& deltaTime) {

    checkAllCollision();
    player->update(deltaTime);
    for (auto& coin: coins) coin->update(deltaTime);
    for (auto& trap: traps) trap->update(deltaTime);
    for (auto& stone: stones) stone->applyPhysics(deltaTime);
    for (auto& wall: walls) wall->update(deltaTime);
    for (auto& enemy: enemies) enemy->update(deltaTime);

    if (!player->health) state = - 1;
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
        std::string path = "assets/fonts/matrix_mono.ttf";
        gFont = TTF_OpenFont(path.c_str(), 15);

        std::string label = "x" + std::to_string(coinsCollected);
        coinsCount->loadFromText(label, {255, 255, 0});
        coinsCount->setPosition({coinHud->getPosition().first + coinHud->getWidth(), coinHud->getPosition().second + 5});
    }

    coinsCount->render();

    for (auto& trap: traps) {
        if (trap->animation->getCurrentFrame().first == 0) trap->animation->setFrame({1, 0});
        trap->render();
    }

    for (auto& button: buttons) button->render();
    for (auto& stone: stones) stone->render();
    for (auto& wall: walls) wall->render();

    door->render();

    for (auto& enemy: enemies) enemy->render();
}

int Map::getState() {

    return state;
}
