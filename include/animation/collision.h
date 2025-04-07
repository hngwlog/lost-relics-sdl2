#pragma once
#include <SDL.h>
#include "../init/graphics.h"

enum COLLISION_STATE {

    NONE = -1,
    LEFT,
    RIGHT,
    TOP,
    DOWN,
    MLEFT,
    MRIGHT,
    MTOP,
    MDOWN
};

class Collision {
public:
    Collision(Texture* body);
    ~Collision();

    int check(Collision* other, bool push = false);

    SDL_FRect getRect() const;

    void move(const float& x, const float& y);

    void debugDraw();

private:
    Texture* body = nullptr;
};
