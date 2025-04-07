#pragma once
#include "../init/graphics.h"
#include "../animation/animation.h"
#include "../animation/collision.h"
#include <vector>

class GameObject {
public:
    GameObject();
    ~GameObject();

    Animation* animation = nullptr;

    void init(std::string path, std::pair<int, int> objSize, std::pair<int, int> position, std::pair<int, int> frameCount, std::vector<std::pair<int, int>> frameLimit);

    bool isChecked = false;
    bool isGrounded = false;
    bool isGroundLeft = false;
    bool isGroundRight = false;
    bool done = false;

    void update(const int& deltaTime);

    void applyPhysics(const int& deltaTime);

    void render();

    Collision* getBox();

    std::pair<int, int> getPosition();

    void setDelayTime(const int& newDelayTime);

    bool getObjState();

private:
    Texture* body = nullptr;
    Collision* box = nullptr;

    std::pair<int, int> objSize;
    std::pair<int, int> objPosition;
    std::pair<int, int> frameCount;
    std::vector<std::pair<int, int>> frameLimit;

    bool checkedAnimationPlayed = false;

    int accumulatedTime = 0;
    int delayTime = 0;

    float gravity = 981;
};
