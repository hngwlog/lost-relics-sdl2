#pragma once
#include "../init/defs.h"
#include "../init/graphics.h"
#include "../animation/animation.h"
#include <string>
#include <vector>

struct MenuItem {

    std::string label;
    Texture* texture;

    int yPos;
};

class HomeScreen {
public:
    HomeScreen();
    ~HomeScreen();

    void init();

    int update(const int& deltaTime);

    void render();

private:
    Texture* gameName = nullptr;
    Texture* background = nullptr;
    std::vector<MenuItem> menuItems;

    Texture* selected = nullptr;
    Animation* selectedAnimation = nullptr;

    int currentState = - 1;
    int timeDelay = 0;
};

