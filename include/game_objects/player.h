#pragma once
#include "../init/graphics.h"
#include "../animation/animation.h"
#include "../animation/collision.h"
#include <vector>

class Player {
public:
    Player(std::pair<int, int> startPosition, bool faceRight);
    ~Player();

    bool isGrounded = false;
    bool isHeadBlocked = false;

    bool isTakingHit = false;

    void handleInput(const int& deltaTime);

    void update(const int& deltaTime);

    void applyPhysics(const int& deltaTime);

    void updateAnimation();

    void takeHit(const int& deltaTime);

    void limitPosition();

    void render();

    Collision* getBox();

private:
    Texture* body;
    Animation* animation;
    Texture* lostHeart;
    Animation* lostHeartAnimation;
    std::vector<Texture*> healthBar;
    Collision* box;

    std::pair<int, int> position;
    bool facingRight;

    int isDashing = 0;
    int dashCooldown = 0;

    bool doneLostHeart = false;
    int health = 4;
    int healDelay = 3000;

    std::pair<int, int> velocity = {0, 0};
    float speed = 200;
    float jumpVelocity = - 600;
    float gravity = 981;
};
