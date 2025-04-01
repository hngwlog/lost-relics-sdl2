#include "../../include/init/defs.h"
#include "../../include/game_state/instruction_screen.h"

InstructionScreen::InstructionScreen() {}

InstructionScreen::~InstructionScreen() {

    delete background;
    delete content;
    delete quit;
}

void InstructionScreen::init() {

    background = new Texture();
    background->loadFromFile("assets/images/background/background.png");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    content = new Texture();
    content->loadFromFile("assets/images/background/tutorial.png");
    content->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    content->setPosition({0, 0});

    std::string path = "assets/fonts/brownie_stencil.ttf";
    gFont = TTF_OpenFont(path.c_str(), 25);

    quit = new Texture();
    quit->loadFromText("PRESS ENTER TO RETURN HOME!", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 525});
}

void InstructionScreen::render() {

    background->render(false);
    content->render(false);
    quit->render(false);
}

