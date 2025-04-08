#include "../../include/init/defs.h"
#include "../../include/game_state/screen.h"

Screen::Screen() {}

Screen::~Screen() {

    delete background;
    delete content;
    delete quit;
}

void Screen::init() {

    background = new Texture();
    background->loadFromFile("assets/images/background/background.png");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 15);

    quit = new Texture();
    quit->loadFromText("PRESS ENTER TO RETURN HOME!", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 525});
}

void Screen::updateText(const std::string& text) {

    std::string path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 15);

    content = new Texture();
    content->loadFromText(text, {255, 255, 255});
    content->setPosition({(SCREEN_WIDTH - content->getWidth()) / 2, 100});
}

void Screen::updateFile(const std::string& path) {

    content = new Texture();
    content->loadFromFile(path.c_str());
    content->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    content->setPosition({0, 0});
}

void Screen::render() {

    background->render(false);
    content->render(false);
    quit->render(false);
}



