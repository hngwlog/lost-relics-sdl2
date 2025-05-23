#include "../../include/init/defs.h"
#include "../../include/game_state/play.h"

Game::Game() {}

Game::~Game() {

    delete chosenMap;
    delete background;
    delete pause;
    delete lose;
    delete win;
    delete quit;
}

void Game::init(int level) {

    std::string path = "assets/data/map/" + std::to_string(level + 1) + ".txt";
    chosenMap = new Map();
    chosenMap->loadMap(path);

    background = new Texture();
    background->loadFromFile("assets/images/background/background.png");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 20);

    pause = new Texture();
    pause->loadFromText("PRESS RETURN TO UNPAUSE!", {255, 255, 255});
    pause->setPosition({(SCREEN_WIDTH - pause->getWidth()) / 2, 300});


    gFont = TTF_OpenFont(path.c_str(), 30);
    lose = new Texture();
    lose->loadFromText("YOU LOSE!", {255, 0, 0});
    lose->setPosition({(SCREEN_WIDTH - lose->getWidth()) / 2, 100});

    win = new Texture();
    win->loadFromText("YOU WIN!", {255, 0, 0});
    win->setPosition({(SCREEN_WIDTH - win->getWidth()) / 2, 100});

    gFont = TTF_OpenFont(path.c_str(), 15);
    quit = new Texture();
    quit->loadFromText("PRESS R TO RETURN LEVEL SELECT OR H TO RETURN HOME", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 300});
}

void Game::update(const int& deltaTime) {

    chosenMap->update(deltaTime);
    state = chosenMap->getState();
}

void Game::render() {

    background->render();
    chosenMap->render();
}

void Game::renderPause() {

    background->render();
    pause->render();
}

int Game::renderLose() {

    background->render();
    lose->render();
    quit->render();
    return chosenMap->score;
}

int Game::renderWin() {

    background->render();
    win->render();
    quit->render();
    return chosenMap->score;
}

int Game::getGameState() {

    return state;
}
