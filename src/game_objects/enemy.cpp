#include "../../include/game_objects/enemy.h"


Enemy::Enemy(std::pair<int, int> startPosition, int type, bool faceRight) {

    switch (type) {
        case 0:
            walkPath = "assets/images/enemy/mushroom/walk.png";
            deathPath = "assets/images/enemy/mushroom/death.png";
            walkFrameCount = {8, 1};
            deathFrameCount = {7, 1};
            speed = 150;
            SIZE = {50, 50};
            break;

        case 1:
            walkPath = "assets/images/enemy/slime/walk.png";
            deathPath = "assets/images/enemy/slime/death.png";
            walkFrameCount = {15, 1};
            deathFrameCount = {7, 1};
            speed = 100;
            SIZE = {50, 50};
            break;
        case 2:
            walkPath = "assets/images/enemy/worm/walk.png";
            deathPath = "assets/images/enemy/worm/death.png";
            walkFrameCount = {6, 1};
            deathFrameCount = {7, 1};
            speed = 75;
            SIZE = {50, 20};
            break;
    }

    body = new Texture();
    body->loadFromFile(walkPath);
    body->setSize(SIZE);
    body->setPosition(startPosition);

    animation = new Animation(walkPath, walkFrameCount, 100);
    animation->initFrameLimit({walkFrameCount.first, 0});

    box = new Collision(body);

    isMovingRight = faceRight;
}

Enemy::~Enemy() {

    delete body;
    delete animation;
    delete box;
}

void Enemy::takeHit() {

    if (hit) return ;

    hit = true;

    animation = new Animation(deathPath, deathFrameCount, 100);
    animation->initFrameLimit({deathFrameCount.first, 0});

    std::pair<int, int> position = body->getPosition();
    body->loadFromFile(deathPath);
    body->setSize(SIZE);
    body->setPosition(position);
}

void Enemy::applyPhysics(const int& deltaTime) {

    float dt = deltaTime / 1000.0f;

    std::pair<int, int> velocity = {0, 0};

    velocity.first += (isMovingRight ? speed : - speed);

    if (!isGrounded) velocity.second += gravity / 2;

    body->move({int(velocity.first * dt), int(velocity.second * dt)});
}

void Enemy::update(const int& deltaTime) {

    if (death) return ;

    applyPhysics(deltaTime);
    animation->update(deltaTime);
    if (hit && animation->isAnimationDone()) death = true;
}

void Enemy::render() {

    if (death) return ;

    body->render(!isMovingRight, animation->getCurrentFrameRect());
}

Collision* Enemy::getBox() {

    return box;
}
