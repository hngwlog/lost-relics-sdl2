#pragma once
#include "../init/graphics.h"
#include "../animation/animation.h"
#include "../animation/collision.h"
#include <vector>

class Attack {
public:
    Attack();
    ~Attack();

    Texture* body;
    Animation* animation;

    int isAttacking = 0;
    int hitCooldown = 0;

    Collision* getBox();

private:
    Collision* box;

};

class Player {
public:
    Player(std::pair<int, int> startPosition, bool faceRight);
    ~Player();

    bool isGrounded = false;
    bool isHeadBlocked = false;

    bool isTakingHit = false;
    int health = 4;
    int healDelay = 1500;

    Attack* attack = nullptr;

    void handleInput(const int& deltaTime);

    void update(const int& deltaTime);

    void applyPhysics(const int& deltaTime);

    void updateAnimation();

    void takeHit(const int& deltaTime);

    void limitPosition();

    void render();

    Collision* getBox();

private:
    Texture* body = nullptr;
    Animation* animation = nullptr;
    Texture* lostHeart = nullptr;
    Animation* lostHeartAnimation = nullptr;
    std::vector<Texture*> healthBar;
    Collision* box;

    std::pair<int, int> position;
    bool facingRight;

    int isDashing = 0;
    int dashCooldown = 0;

    bool doneLostHeart = false;

    std::pair<int, int> velocity = {0, 0};
    float speed = 200;
    float jumpVelocity = - 600;
    float gravity = 981;
};
