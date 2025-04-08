#include "../../include/init/defs.h"
#include "../../include/game_state/quit_screen.h"

QuitScreen::QuitScreen() {}

QuitScreen::~QuitScreen() {

    delete background;
    delete quit;
}

void QuitScreen::init() {

    background = new Texture();
    background->loadFromFile("assets/images/background/background.png");
    background->setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    background->setPosition({0, 0});

    std::string path = "assets/fonts/matrix_mono.ttf";
    gFont = TTF_OpenFont(path.c_str(), 20);

    quit = new Texture();
    quit->loadFromText("ARE YOU SURE TO QUIT? Y/N", {255, 255, 255});
    quit->setPosition({(SCREEN_WIDTH - quit->getWidth()) / 2, 200});
}

void QuitScreen::render() {

    background->render(false);
    quit->render(false);
}
