#pragma once
#include "../init/graphics.h"
#include "../animation/animation.h"
#include "../animation/collision.h"
#include <vector>

class GameObject {
public:
    GameObject();
    ~GameObject();

    void init(std::string path, std::pair<int, int> objSize, std::pair<int, int> position, std::pair<int, int> frameCount, std::vector<std::pair<int, int>> frameLimit);

    bool isChecked = false;

    void update(const int& deltaTime);

    void render();

    Collision* getBox();

private:
    Texture* body = nullptr;
    Animation* animation = nullptr;
    Collision* box = nullptr;

    std::pair<int, int> objSize;
    std::pair<int, int> objPosition;
    std::pair<int, int> frameCount;
    std::vector<std::pair<int, int>> frameLimit;

    bool checkedAnimationPlayed = false;
    bool done = false;
};
