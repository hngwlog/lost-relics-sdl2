#include "../../include/init/defs.h"
#include "../../include/game_state/level_select_screen.h"
#include <fstream>

LevelSelectScreen::LevelSelectScreen() {};

LevelSelectScreen::~LevelSelectScreen() {

    std::string path = "assets/data/high_score/high_score.txt";
    std::ofstream scoreFile(path);
    if (scoreFile.fail()) logErrorAndExit("Could not load score file!", "level_select_screen.cpp");

    for (auto& level: levels) scoreFile << level.score << '\n';

    scoreFile.close();

    delete background;
    delete title;
    for (auto& level: levels) {
        delete level.texture;
        delete level.highScore;
    }
    delete quit;
}

void LevelSelectScreen::init(int totalLevels) {

    background = new Texture();
    background->loadFromFile("assets/images/background/home_screen.jpg");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 20);

    title = new Texture();
    title->loadFromText("Please select your level!", {255, 255, 255});
    title->setPosition({(SCREEN_WIDTH - title->getWidth()) / 2, 100});

    gFont = TTF_OpenFont(path.c_str(), 15);

    int yStart = 200;

    path = "assets/data/high_score/high_score.txt";
    std::ifstream scoreFile(path.c_str());
    if (scoreFile.fail()) logErrorAndExit("Could not load high score file! %s\n", "level_select_screen.cpp");

    for (int i = 0; i < totalLevels; i++) {
        Level level;
        level.label = "Level " + std::to_string(i + 1) + (i > 0 ? " - Coming soon..." : "");
        level.texture = new Texture();
        level.texture->loadFromText(level.label, {255, 255, 255});
        level.yPos = yStart;
        level.texture->setPosition({100, level.yPos});
        scoreFile >> level.score;
        std::string scoreLabel = "HI: " + std::to_string(level.score);
        level.highScore = new Texture();
        level.highScore->loadFromText(scoreLabel, {255, 255, 255});
        level.highScore->setPosition({600, level.yPos});
        levels.push_back(level);
        yStart += 40;

    }

    scoreFile.close();

    path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 15);

    quit = new Texture();
    quit->loadFromText("Press ESC to return home!", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 500});

    isLevelUnlocked.assign(totalLevels, false);
    isLevelUnlocked[0] = true;
}

int LevelSelectScreen::update(const int& deltaTime) {

    int previousState = currentState;

    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

    if (timeDelay <= 0) {
        timeDelay = 200;
        if (currentKeyState[SDL_SCANCODE_DOWN]) {
            selectSound->play(0);

            currentState++;
        }
        else if (currentKeyState[SDL_SCANCODE_UP]) {
            selectSound->play(0);

            currentState--;
        }
        else if (currentKeyState[SDL_SCANCODE_RETURN]) {
            selectSound->play(0);

            return currentState;
        }
        else if (currentKeyState[SDL_SCANCODE_ESCAPE]) {
            selectSound->play(0);

            return - 2;
        }
    }

    currentState = (currentState + unlockedLevels) % unlockedLevels;
    timeDelay -= deltaTime;

    if (currentState != previousState) {
        std::string path = "assets/fonts/matrix_mono.ttf";
        gFont = TTF_OpenFont(path.c_str(), 15);

        /** Reset previous selected label */
        if (previousState != - 1) levels[previousState].texture->loadFromText(levels[previousState].label, {255, 255, 255});

        /** Highlight selected level */
        std::string selectedLabel = "> " + levels[currentState].label;
        levels[currentState].texture->loadFromText(selectedLabel, {255, 0, 0});
        levels[currentState].texture->setPosition({100, levels[currentState].yPos});
    }

    return - 1;
}

void LevelSelectScreen::unlockLevel(int level) {

    if (isLevelUnlocked[level] == false) {
        isLevelUnlocked[level] = true;
        unlockedLevels++;
    }
}

void LevelSelectScreen::render() {

    background->render(false);
    title->render(false);
    for (auto& level: levels) {
        level.texture->render();
        if (level.previousScore != level.score) {
            std::string scoreLabel = "HI: " + std::to_string(level.score);
            level.highScore->loadFromText(scoreLabel, {255, 255, 255});
            level.highScore->setPosition({600, level.yPos});
        }
        level.previousScore = level.score;
        level.highScore->render();
    }
    quit->render(false);
}
