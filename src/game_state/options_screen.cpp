#include "../../include/init/defs.h"
#include "../../include/game_state/options_screen.h"

OptionsScreen::OptionsScreen() {}

OptionsScreen::~OptionsScreen() {

    delete background;
    delete content;
    delete quit;
}

void OptionsScreen::init() {

    background = new Texture();
    background->loadFromFile("assets/images/background/background.png");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 15);

    content = new Texture();
    content->loadFromText("This feature will be update soon!", {255, 255, 255});
    content->setPosition({(SCREEN_WIDTH - content->getWidth()) / 2, 100});

    quit = new Texture();
    quit->loadFromText("PRESS ENTER TO RETURN HOME!", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 525});
}

void OptionsScreen::render() {

    background->render(false);
    content->render(false);
    quit->render(false);
}


