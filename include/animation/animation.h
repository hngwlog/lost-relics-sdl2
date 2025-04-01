#pragma once
#include <SDL.h>
#include <string>

class Animation {
public:
    Animation(const std::string& filePath, std::pair<int, int> frameCount, int switchTime);
    ~Animation();

    void update(const int& deltaTime, bool flip = false);

    void initFrameLimit(std::pair<int, int> newFrameLimit);

    void setFrame(std::pair<int, int> frame);

    void setFrameLimit(std::pair<int, int> newFrameLimit);

    void setFlip(bool flip);

    std::pair<int, int> getCurrentFrame();

    SDL_Rect* getCurrentFrameRect();

    bool isAnimationDone() const;

private:
    SDL_Surface* spriteSheet = nullptr;
    SDL_Rect frameRect;

    std::pair<int, int> totalFrames;
    int timePerFrame;
    std::pair<int, int> frameLimit;
    int frameWidth, frameHeight;
    std::pair<int, int> currentFrame;
    int accumulatedTime = 0;
    bool facingRight = true;
    bool animationDone = false;
};
