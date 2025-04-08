#pragma once
#include "../init/graphics.h"

class Screen {
public:
    Screen();
    ~Screen();

    void init();

    void updateText(const std::string& text);

    void updateFile(const std::string& path);

    void render();

private:
    Texture* background = nullptr;
    Texture* content = nullptr;
    Texture* quit = nullptr;
};
