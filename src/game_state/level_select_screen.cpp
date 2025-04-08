#include "../../include/init/defs.h"
#include "../../include/game_state/level_select_screen.h"

LevelSelectScreen::LevelSelectScreen() {};

LevelSelectScreen::~LevelSelectScreen() {

    delete background;
    delete title;
    for (auto& level: levels) delete level.texture;
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

    for (int i = 0; i < totalLevels; i++) {
        Level level;
        level.label = "Level " + std::to_string(i + 1) + (i > 0 ? " - Coming soon..." : "");
        level.texture = new Texture();
        level.texture->loadFromText(level.label, {255, 255, 255});
        level.yPos = yStart;
        level.texture->setPosition({100, level.yPos});
        levels.push_back(level);
        yStart += 40;
    }

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
        if (currentKeyState[SDL_SCANCODE_DOWN]) currentState++;
        else if (currentKeyState[SDL_SCANCODE_UP]) currentState--;
        else if (currentKeyState[SDL_SCANCODE_RETURN]) return currentState;
        else if (currentKeyState[SDL_SCANCODE_ESCAPE]) return - 2;
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
    for (auto& level: levels) level.texture->render(false);
    quit->render(false);
}
