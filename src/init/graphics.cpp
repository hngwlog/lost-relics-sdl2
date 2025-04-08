#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../../include/init/defs.h"
#include "../../include/init/graphics.h"

bool initSDL() {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) logErrorAndExit("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

    gWindow = SDL_CreateWindow("Lost Relics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) logErrorAndExit("Window could not be created! SDL_Error: %s\n ", SDL_GetError());

    gRenderer = SDL_CreateRenderer(gWindow, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) logErrorAndExit("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());

    if (!(IMG_Init(IMG_INIT_PNG))) logErrorAndExit("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());

    if (TTF_Init() == - 1) logErrorAndExit("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) logErrorAndExit("SDL_mixer could not initialize! Mixer_Error: %s\n", Mix_GetError());

    SDL_Surface* icon = IMG_Load("assets/images/icon/icon.jpg");
    SDL_SetWindowIcon(gWindow, icon);

    return true;
}

bool initMusic() {

    gameMusic = new MusicManager();
    gameMusic->load("assets/sounds/game_music.mp3");

    jumpSound = new MusicManager();
    jumpSound->load("assets/sounds/jump.wav");
    jumpSound->setVolume(10);

    coinSound = new MusicManager();
    coinSound->load("assets/sounds/coin.wav");
    coinSound->setVolume(15);

    dashSound = new MusicManager();
    dashSound->load("assets/sounds/dash.wav");
    dashSound->setVolume(25);

    attackSound = new MusicManager();
    attackSound->load("assets/sounds/attack.wav");
    attackSound->setVolume(60);

    selectSound = new MusicManager();
    selectSound->load("assets/sounds/select.mp3");
    selectSound->setVolume(70);

    hitEnemySound = new MusicManager();
    hitEnemySound->load("assets/sounds/hit_enemy.wav");
    hitEnemySound->setVolume(50);

    loseSound = new MusicManager();
    loseSound->load("assets/sounds/lose.wav");
    loseSound->setVolume(80);

    winSound = new MusicManager();
    winSound->load("assets/sounds/win.wav");
    winSound->setVolume(80);

    return true;
}

Texture::Texture() {

    width = 0;
    height = 0;
    texture = nullptr;
}

Texture::~Texture() {

    free();
}

bool Texture::loadFromText(std::string text, SDL_Color textColor) {

    /** Render text surface */
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface == nullptr) logErrorAndExit("Unabe to render text surface! TTF_Error: %s\n", TTF_GetError());

    /** Create texture from surface pixels */
    texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (texture == nullptr) logErrorAndExit("Unable to create texture from renderer text! SDL_Erro: %s\n", SDL_GetError());

    width = textSurface->w;
    height = textSurface->h;
    rect.w = width;
    rect.h = height;

    /** Get rid of old surface */
    SDL_FreeSurface(textSurface);

    return true;
}

bool Texture::loadFromFile(std::string path) {

    /** Load image at specified path */
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) logErrorAndExit("Unable to load image! IMG_Error: %s\n", IMG_GetError());

    /** Create texture from surface pixels */
    texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (texture == nullptr) logErrorAndExit("Unable to create texture! SDL_Error: %s\n", SDL_GetError());

    width = loadedSurface->w;
    height = loadedSurface->h;
    rect.w = width;
    rect.h = height;

    /** Get rid of old surface */
    SDL_FreeSurface(loadedSurface);

    return true;
}

void Texture::render(bool flip, SDL_Rect* clip, double angle, SDL_Point* center) {

    if (texture == nullptr) return ;
    if (flip) SDL_RenderCopyEx(gRenderer, texture, clip, &rect, angle, center, SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopyEx(gRenderer, texture, clip, &rect, angle, center, SDL_FLIP_NONE);
}

void Texture::setSize(std::pair<int, int> size) {

    width = size.first;
    height = size.second;
    rect.w = width;
    rect.h = height;
}

void Texture::setPosition(std::pair<int, int> pos) {

    rect.x = pos.first;
    rect.y = pos.second;
}

void Texture::move(std::pair<int, int> addPos) {

    rect.x += addPos.first;
    rect.y += addPos.second;
}

int Texture::getWidth() {

    return width;
}

int Texture::getHeight() {

    return height;
}

std::pair<int, int> Texture::getSize() {

    return {width, height};
}

std::pair<int, int> Texture::getPosition() {

    return {rect.x, rect.y};
}

void Texture::free() {

    SDL_DestroyTexture(texture);
    width = 0;
    height = 0;
    texture = nullptr;
}

void Texture::debugInfo() {

    std::cerr << "Texture pos: (" << rect.x << "," << rect.y << "), size: (" << width << "," << height << ")\n";
}
