#pragma once
#include "../init/graphics.h"

class QuitScreen {
public:
    QuitScreen();
    ~QuitScreen();

    void init();

    void render();

private:
    Texture* background = nullptr;
    Texture* quit = nullptr;
};
