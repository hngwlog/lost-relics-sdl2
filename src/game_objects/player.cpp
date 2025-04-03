#include "../../include/game_objects/player.h"
#include "../../include/init/defs.h"

Player::Player(std::pair<int, int> startPosition, bool faceRight)
    : position(startPosition), facingRight(faceRight) {

    body = new Texture();
    body->loadFromFile("assets/images/hero/hero.png");
    body->setSize({50, 50});
    body->setPosition(startPosition);

    animation = new Animation("assets/images/hero/hero.png", {8, 15}, 100);
    animation->initFrameLimit({3, 6});

    lostHeart = new Texture();
    lostHeart->loadFromFile("assets/images/hud/lost_hearts.png");
    lostHeart->setSize({30, 30});

    lostHeartAnimation = new Animation("assets/images/hud/lost_hearts.png", {5, 1}, 100);

    int xStart = 95;
    for (int i = 0; i < health; i++) {
        Texture* health = new Texture();
        health->loadFromFile("assets/images/hud/hearts_hud.png");
        health->setSize({25, 25});
        health->setPosition({xStart, 20});
        xStart += 30;
        healthBar.push_back(health);
    }

    box = new Collision(body);
}

Player::~Player() {

    delete body;
    delete animation;
    delete lostHeart;
    delete lostHeartAnimation;
    for (auto& health: healthBar) delete health;
    delete box;
}

void Player::handleInput(const int& deltaTime) {

    const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

    if (isGrounded) velocity.second = 0;

    if (isDashing > 0) {
        velocity.first += speed * (facingRight ? 1 : - 1);
        isDashing--;
    }
    else {
        velocity.first = 0;

        if (currentKeyState[SDL_SCANCODE_LEFT]) {
            velocity.first -= speed;
            facingRight = false;
        }
        if (currentKeyState[SDL_SCANCODE_RIGHT]) {
            velocity.first += speed;
            facingRight = true;
        }
        if (currentKeyState[SDL_SCANCODE_SPACE] && isGrounded) {
            velocity.second = jumpVelocity;
            isGrounded = false;
        }
    }
    if (currentKeyState[SDL_SCANCODE_D] && !isDashing && dashCooldown <= 0) {
        dashCooldown = 1000;
        isDashing = 8;
        velocity = {0, 0};
    }

    dashCooldown -= deltaTime;
}

void Player::update(const int& deltaTime) {

    if (isTakingHit == false) {
        handleInput(deltaTime);
        applyPhysics(deltaTime);
        updateAnimation();
        animation->update(deltaTime);
    }
    else {
        applyPhysics(deltaTime);
        takeHit(deltaTime);
        animation->update(deltaTime);
    }
    limitPosition();
}

void Player::applyPhysics(const int& deltaTime) {

    float dt = deltaTime / 1000.0f;

    if (!isGrounded) velocity.second += gravity * dt;

    if (isHeadBlocked && velocity.second < 0) velocity.second = gravity * dt;

    body->move({int(velocity.first * dt), int(velocity.second * dt)});
}

void Player::updateAnimation() {

    if (isDashing) {
        if (isDashing == 8) {
            animation->initFrameLimit({3, 8});
            animation->setFrame({2, 8});
        }
    }
    else if (!isGrounded) {
        if (velocity.second < 0) animation->setFrameLimit({3, 7}); /** Jump */
        else animation->setFrameLimit({3, 6}); /** Fall */
    }
    else if (velocity.first != 0) animation->setFrameLimit({6, 1}); /** Run */
    else animation->setFrameLimit({4, 5}); /** Idle */

    animation->setFlip(facingRight);
}

void Player::takeHit(const int& deltaTime) {

    if (healDelay == 3000) {
        lostHeart->setPosition(healthBar[health - 1]->getPosition());
        lostHeartAnimation->initFrameLimit({5, 0});
        doneLostHeart = false;
    }

    animation->setFrameLimit({3, 8});

    healDelay -= deltaTime;

    if (healDelay <= 0) {
        health--;

        isTakingHit = false;
        healDelay = 3000;

        animation->setFrameLimit({4, 5});
    }

    lostHeartAnimation->update(deltaTime);

    if (lostHeartAnimation->isAnimationDone() && !doneLostHeart) doneLostHeart = true;
}

void Player::limitPosition() {

    if (body->getPosition().first < 0) body->setPosition({0, body->getPosition().second});

    if (body->getPosition().first + body->getSize().first > SCREEN_WIDTH) body->setPosition({SCREEN_WIDTH - body->getSize().first, body->getPosition().second});
}

void Player::render() {

    body->render(!animation->getFlip(), animation->getCurrentFrameRect());

    /** Render health bar */
    for (int i = 0; i < health - 1; i++) healthBar[i]->render(false);
    if (!isTakingHit) healthBar[health - 1]->render(false);
    else if (!doneLostHeart) lostHeart->render(false, lostHeartAnimation->getCurrentFrameRect());
}

Collision* Player::getBox() {

    return box;
}
