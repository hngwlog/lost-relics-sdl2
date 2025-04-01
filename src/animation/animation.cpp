#include <SDL_image.h>
#include "../../include/init/defs.h"
#include "../../include/animation/animation.h"

Animation::Animation(const std::string& filePath, std::pair<int, int> frameCount, int switchTime)
    : totalFrames(frameCount), timePerFrame(switchTime), frameLimit({frameCount.first, 0}) {

    spriteSheet = IMG_Load(filePath.c_str());
    if (spriteSheet == nullptr) logErrorAndExit("Failed to load sprite sheet! IMG_Error: %s\n", IMG_GetError());

    frameWidth = spriteSheet->w / totalFrames.first;
    frameHeight = spriteSheet->h / totalFrames.second;

    frameRect = {0, 0, frameWidth, frameHeight};
    currentFrame = {0, 0};
}

Animation::~Animation() {

    if (spriteSheet != nullptr) {
        SDL_FreeSurface(spriteSheet);
        spriteSheet = nullptr;
    }
}

void Animation::update(const int& deltaTime, bool flip) {

    accumulatedTime += deltaTime;

    animationDone = false;

    if (accumulatedTime >= timePerFrame) {
        accumulatedTime -= timePerFrame;
        if (currentFrame.second != frameLimit.second) currentFrame = {0, frameLimit.second};
        else {
            if (!flip) {
                currentFrame.first++;
                if (currentFrame.first >= frameLimit.first) {
                    currentFrame.first = 0;
                    animationDone = true;
                }
            }
            else {
                currentFrame.first--;
                if (currentFrame.first < 0) {
                    currentFrame.first = frameLimit.first - 1;
                    animationDone = true;
                }
            }
        }
        frameRect.x = currentFrame.first * frameWidth;
        frameRect.y = currentFrame.second * frameHeight;
    }
}

void Animation::initFrameLimit(std::pair<int, int> newFrameLimit) {

    frameLimit = newFrameLimit;
    currentFrame = {0, frameLimit.second};
    frameRect.x = currentFrame.first * frameWidth;
    frameRect.y = currentFrame.second * frameHeight;
    animationDone = false;
}

void Animation::setFrame(std::pair<int, int> frame) {

    currentFrame = frame;
    frameRect.x = currentFrame.first * frameWidth;
    frameRect.y = currentFrame.second * frameHeight;
}

void Animation::setFrameLimit(std::pair<int, int> newFrameLimit) {

    if (currentFrame.second == newFrameLimit.second) return ;

    frameLimit = newFrameLimit;
    currentFrame = {0, frameLimit.second};
    frameRect.x = currentFrame.first * frameWidth;
    frameRect.y = currentFrame.second * frameHeight;
    animationDone = false;
}

void Animation::setFlip(bool flip) {

    facingRight = flip;
}

std::pair<int, int> Animation::getCurrentFrame() {

    return currentFrame;
}

SDL_Rect* Animation::getCurrentFrameRect() {

    return &frameRect;
}

bool Animation::isAnimationDone() const {

    return animationDone;
}
