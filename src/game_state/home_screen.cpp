#include "../../include/game_state/home_screen.h"

HomeScreen::HomeScreen() {}

HomeScreen::~HomeScreen() {

    delete background;
    delete gameName;

    for (auto& menuItem: menuItems) delete menuItem.texture;
}

void HomeScreen::init() {

    timeDelay = 0;

    background = new Texture();
    background->loadFromFile("assets/images/background/home_screen.jpg");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/cowboy_adventure.ttf";
    gFont = TTF_OpenFont(path.c_str(), 50);

    gameName = new Texture();
    gameName->loadFromText("Lost Relics", {255, 255, 255});
    gameName->setPosition({(SCREEN_WIDTH - gameName->getWidth()) / 2, 100});

    gFont = TTF_OpenFont(path.c_str(), 20);
    std::vector<std::string> labels = {"Start", "Instruction", "Options", "Quit"};

    int yStart = 300;

    for (const auto& label: labels) {
        MenuItem item;
        item.label = label;
        item.texture = new Texture();
        item.texture->loadFromText(label, {255, 255, 255});
        item.yPos = yStart;
        yStart += 50;
        menuItems.push_back(item);
        menuItems.back().texture->setPosition({(SCREEN_WIDTH - menuItems.back().texture->getWidth()) / 2, menuItems.back().yPos});
    }
}

void HomeScreen::render() {

    background->render(false);
    gameName->render(false);

    for (auto& menuItem: menuItems) menuItem.texture->render(false);
}

int HomeScreen::update(const int& deltaTime) {

    int previousState = currentState;

    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

    if (timeDelay <= 0) {
        timeDelay = 200;

        if (currentKeyState[SDL_SCANCODE_DOWN]) currentState++;
        else if (currentKeyState[SDL_SCANCODE_UP]) currentState--;
        else if (currentKeyState[SDL_SCANCODE_RETURN]) return currentState;
    }

    currentState = (currentState + (int)menuItems.size()) % (int)menuItems.size();
    timeDelay -= deltaTime;

    if (currentState != previousState) {
        /** Reset previous selected label */
        if (previousState != - 1) menuItems[previousState].texture->loadFromText(menuItems[previousState].label, {255, 255, 255});

        /** Highlight selected menu item */
        std::string selectedLabel = "> " + menuItems[currentState].label;
        menuItems[currentState].texture->loadFromText(selectedLabel, {255, 255, 255});
        menuItems[currentState].texture->setPosition({(SCREEN_WIDTH - menuItems[currentState].texture->getWidth()) / 2 + 10, menuItems[currentState].yPos});
    }
    return - 1;
}

