#pragma once
#include "../init/graphics.h"
#include "../animation/animation.h"
#include <vector>

class GameObject {
public:
    GameObject(std::string path, std::pair<int, int> objSize, std::pair<int, int> position, std::pair<int, int> frameCount, std::vector<std::pair<int, int>> frameLimit);
    ~GameObject();

    bool isChecked = false;

    void update(const int& deltaTime);

    void render();

private:
    Texture* body;
    Animation* animation;
    std::pair<int, int> objSize;
    std::pair<int, int> objPosition;
    std::pair<int, int> frameCount;
    std::vector<std::pair<int, int>> frameLimit;

    bool checkedAnimationPlayed = false;
    bool done = false;
};
