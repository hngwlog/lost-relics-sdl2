#include "../../include/game_state/home_screen.h"

HomeScreen::HomeScreen() {}

HomeScreen::~HomeScreen() {

    delete background;
    delete gameName;

    for (auto& menuItem: menuItems) delete menuItem.texture;

    delete selected;
    delete selectedAnimation;
}

void HomeScreen::init() {

    timeDelay = 0;

    background = new Texture();
    background->loadFromFile("assets/images/background/home_screen.jpg");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/karmatic_arcade.ttf";
    gFont = TTF_OpenFont(path.c_str(), 70);

    gameName = new Texture();
    gameName->loadFromText("Lost Relics", {255, 255, 255});
    gameName->setPosition({(SCREEN_WIDTH - gameName->getWidth()) / 2, 100});

    gFont = TTF_OpenFont(path.c_str(), 30);
    std::vector<std::string> labels = {"Start", "Instruction", "Options", "Quit"};

    int yStart = 300;

    for (const auto& label: labels) {
        MenuItem item;
        item.label = label;
        item.texture = new Texture();
        item.texture->loadFromText(label, {255, 255, 255});
        item.yPos = yStart;
        menuItems.push_back(item);
        menuItems.back().texture->setPosition({(SCREEN_WIDTH - menuItems.back().texture->getWidth()) / 2, menuItems.back().yPos});
        yStart += 50;
    }

    selected = new Texture();
    selected->loadFromFile("assets/images/hud/select_icon.png");
    selected->setSize({25, 25});

    selectedAnimation = new Animation("assets/images/hud/select_icon.png", {5, 1}, 100);
}

void HomeScreen::render() {

    background->render(false);
    gameName->render(false);

    for (auto& menuItem: menuItems) menuItem.texture->render(false);

    selected->render(false, selectedAnimation->getCurrentFrameRect());
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
        selected->setPosition({(SCREEN_WIDTH - menuItems[currentState].texture->getWidth()) / 2 - selected->getWidth() - 20, menuItems[currentState].yPos + 5});
    }

    selectedAnimation->update(deltaTime);

    return - 1;
}

