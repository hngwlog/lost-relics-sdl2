#pragma once
#include "../init/graphics.h"

class InstructionScreen {
public:
    InstructionScreen();
    ~InstructionScreen();

    void init();

    void render();

private:
    Texture* background = nullptr;
    Texture* content = nullptr;
    Texture* quit = nullptr;
};
