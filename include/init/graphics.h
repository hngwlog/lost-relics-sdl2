#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

bool initSDL();

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromText(std::string text, SDL_Color textColor);

    bool loadFromFile(std::string path);

    void render(bool flip = 0, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr);

    void setSize(std::pair<int, int> size);

    void setPosition(std::pair<int, int> pos);

    void move(std::pair<int, int> addPos);

    int getWidth();

    int getHeight();

    std::pair<int, int> getSize();

    std::pair<int, int> getPosition();

    void free();

    void debugInfo();

private:
    int width, height;
    SDL_Rect rect;
    SDL_Texture* texture = nullptr;
};

#endif // _GRAPHICS__H
