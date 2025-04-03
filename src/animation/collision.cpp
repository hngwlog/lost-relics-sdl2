#include "../../include/animation/collision.h"
#include "../../include/init/defs.h"

Collision::Collision(Texture* body): body(body) {}

Collision::~Collision() {

    delete body;
}

int Collision::check(Collision* other, bool push) {

    /** AABB Collision Detection (Axis-Aligned Bounding Box) */

    SDL_FRect thisRect = getRect();
    SDL_FRect otherRect = other->getRect();

    float deltaX = (otherRect.x + otherRect.w * 0.5f) - (thisRect.x + thisRect.w * 0.5f);
    float deltaY = (otherRect.y + otherRect.h * 0.5f) - (thisRect.y + thisRect.h * 0.5f);

    float overlapX = (thisRect.w + otherRect.w) * 0.5f - abs(deltaX);
    float overlapY = (thisRect.h + otherRect.h) * 0.5f - abs(deltaY);

    if (overlapX > 0 && overlapY > 0) {

        /** Prefer the less intersecting part */
        if (overlapX < overlapY) {
            if (deltaX > 0) {
                /** this -> other */
                if (push) other->move(thisRect.x + thisRect.w - otherRect.x, 0);
                return COLLISION_STATE::RIGHT;
            }
            else {
                /** other -> this */
                if (push) other->move(- (otherRect.x + otherRect.w - thisRect.x), 0);
                return COLLISION_STATE::LEFT;
            }
        }
        else {
            if (deltaY > 0) {
                /**
                    this
                    other
                */
                if (push) other->move(0, thisRect.y + thisRect.h - otherRect.y);
                return COLLISION_STATE::DOWN;
            }
            else {
                /**
                    other
                    this
                */
                if (push) other->move(0, - (otherRect.y + otherRect.h - thisRect.y));
                return COLLISION_STATE::TOP;
            }
        }
    }

    if (overlapX == 0 && overlapY > 0) {
        if (deltaX > 0) return COLLISION_STATE::MRIGHT;
        return COLLISION_STATE::MLEFT;
    }
    if (overlapX > 0 && overlapY == 0) {
        if (deltaY > 0) return COLLISION_STATE::MDOWN;
        return COLLISION_STATE::MTOP;
    }
    return COLLISION_STATE::NONE;
}

SDL_FRect Collision::getRect() const {

    std::pair<int, int> pos = body->getPosition();
    std::pair<int, int> size = body->getSize();
    return {pos.first, pos.second, size.first, size.second};
}

void Collision::move(const int& x, const int& y) {

    body->move({int(x), int(y)});
}

void Collision::debugDraw() {

    SDL_FRect rect = getRect();
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    SDL_RenderDrawRectF(gRenderer, &rect);
}
