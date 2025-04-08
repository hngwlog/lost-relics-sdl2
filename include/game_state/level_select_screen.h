#pragma once
#include "../init/graphics.h"
#include <string>
#include <vector>

struct Level {

    std::string label;
    Texture* texture;

    int previousScore = - 1;
    int score;
    Texture* highScore;

    int yPos;
};

class LevelSelectScreen {
public:
    LevelSelectScreen();
    ~LevelSelectScreen();

    std::vector<bool> isLevelUnlocked;
    std::vector<Level> levels;

    void init(int totalLevels);

    int update(const int& deltaTime);

    void unlockLevel(int level);

    void render();

private:
    Texture* background = nullptr;
    Texture* title = nullptr;
    Texture* quit = nullptr;
    int unlockedLevels = 0;
    int currentState = - 1;
    int timeDelay = 0;
};
