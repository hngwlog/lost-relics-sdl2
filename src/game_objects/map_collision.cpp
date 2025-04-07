#include "../../include/game_objects/map.h"

void Map::playerAndTiles() {

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

void Map::playerAndCoins() {

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

void Map::playerAndTraps() {

    if (!player->isTakingHit) {
        for (auto& trap: traps) {
            if (!trap->getObjState()) continue;
            if (player->getBox()->check(trap->getBox(), false) != COLLISION_STATE::NONE) player->isTakingHit = true;
        }
    }
}

void Map::playerAndStones() {

    for (auto& stone: stones) {
        int state = player->getBox()->check(stone->getBox(), false);
        if (state == COLLISION_STATE::LEFT) {
            if (stone->isGroundLeft) stone->getBox()->check(player->getBox(), true);
            else player->getBox()->check(stone->getBox(), true);
        }
        else if (state == COLLISION_STATE::RIGHT) {
            if (stone->isGroundRight) stone->getBox()->check(player->getBox(), true);
            else player->getBox()->check(stone->getBox(), true);
        }
        else if (state == COLLISION_STATE::DOWN || state == COLLISION_STATE::MDOWN) {
            player->isGrounded = true;
            stone->getBox()->check(player->getBox(), true);
        }
    }
}

void Map::stonesAndTiles() {

    for (auto& stone: stones) {
        stone->isGrounded = false;
        stone->isGroundLeft = false;
        stone->isGroundRight = false;
        for (int i = 0; i < CNT_BLOCK_Y; i++) {
            for (int j = 0; j < CNT_BLOCK_X; j++) {
                if (tiles[i][j].getBox() == nullptr) continue;
                int state = tiles[i][j].getBox()->check(stone->getBox(), true);
                if (state == COLLISION_STATE::TOP || state == COLLISION_STATE::MTOP) stone->isGrounded = true;
                else if (state == COLLISION_STATE::RIGHT || state == COLLISION_STATE::MRIGHT) stone->isGroundLeft = true;
                else if (state == COLLISION_STATE::LEFT || state == COLLISION_STATE::MLEFT) stone->isGroundRight = true;
            }
        }
    }
}

void Map::buttonsAndStones() {

    for (int i = 0; i < totalWalls; i++) {
        buttons[i]->isChecked = false;
        for (auto& stone: stones) {
            if (buttons[i]->getBox()->check(stone->getBox(), true) != COLLISION_STATE::NONE) buttons[i]->isChecked = true;
        }
        if (buttons[i]->getBox()->check(player->getBox(), true) != COLLISION_STATE::NONE) buttons[i]->isChecked = true;
        walls[i]->isChecked = buttons[i]->isChecked;
    }
}

void Map::playerAndWalls() {

    for (auto& wall: walls) {
        if (wall->done) continue;
        wall->getBox()->check(player->getBox(), true);
    }
}

void Map::playerAndDoor() {

    if (player->getBox()->check(door->getBox(), false) != COLLISION_STATE::NONE) state = 1;
}

void Map::checkAllCollision() {

    playerAndTiles();
    playerAndCoins();
    playerAndTraps();
    playerAndStones();
    stonesAndTiles();
    buttonsAndStones();
    playerAndWalls();
    playerAndDoor();
}
