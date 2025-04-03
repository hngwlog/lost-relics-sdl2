#include "../../include/game_objects/game_object.h"

GameObject::GameObject() {}

GameObject::~GameObject() {

    delete body;
    delete animation;
    delete box;
}

void GameObject::init(std::string path, std::pair<int, int> size, std::pair<int, int> position, std::pair<int, int> frame, std::vector<std::pair<int, int>> limit) {

    objSize = size;
    objPosition = position;
    frameCount = frame;
    frameLimit = limit;

    body = new Texture();
    body->loadFromFile(path.c_str());
    body->setSize({objSize});
    body->setPosition({objPosition});

    animation = new Animation(path.c_str(), frameCount, 100);

    box = new Collision(body);
}

void GameObject::update(const int& deltaTime) {

    if (!isChecked && animation->getCurrentFrame().second != 0) {
        animation->update(deltaTime, true);
        if (animation->isAnimationDone()) {
            animation->initFrameLimit({frameLimit[0].first, 0});
            checkedAnimationPlayed = false;
        }
        done = false;
        return ;
    }
    if (done) return ;
    if (isChecked && !checkedAnimationPlayed) {
        if (frameCount.second > 1) animation->initFrameLimit({frameLimit[1].first, 1});
        checkedAnimationPlayed = true;
    }
    animation->update(deltaTime);
    if (animation->isAnimationDone() && checkedAnimationPlayed) done = true;
}

void GameObject::render() {

    if (done || body == nullptr) return ;

    body->render(false, animation->getCurrentFrameRect());
}

Collision* GameObject::getBox() {

    return box;
}
