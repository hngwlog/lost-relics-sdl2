#pragma once
#include "../init/graphics.h"

class OptionsScreen {
public:
    OptionsScreen();
    ~OptionsScreen();

    void init();

    void render();

private:
    Texture* background = nullptr;
    Texture* content = nullptr;
    Texture* quit = nullptr;
};
