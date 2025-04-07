#pragma once;
#include "../init/graphics.h"
#include "../animation/animation.h"
#include "../animation/collision.h"

class Enemy {
public:
    Enemy(std::pair<int, int> startPosition, int type, bool faceRight);
    ~Enemy();

    std::string walkPath, deathPath;
    std::pair<int, int> walkFrameCount, deathFrameCount, SIZE;

    bool isMovingRight;
    bool isGrounded = true;
    bool hit = false;
    bool death = false;

    void takeHit();

    void applyPhysics(const int& deltaTime);

    void update(const int& deltaTime);

    void render();

    Collision* getBox();

private:
    Texture* body = nullptr;
    Animation* animation = nullptr;
    Collision* box = nullptr;

    float speed;
    float gravity = 981;
};
