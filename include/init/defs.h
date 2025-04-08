#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "music_manager.h"
#include <random>
#include <chrono>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

extern TTF_Font* gFont;

extern MusicManager *gameMusic, *jumpSound, *coinSound, *dashSound, *attackSound, *selectSound, *hitEnemySound, *loseSound, *winSound;

enum HOMESCREEN {

    START,
    INSTRUCTION,
    OPTIONS,
    QUIT,
    HOME
};

void logErrorAndExit(const char* msg, const char* error);

long long random(long long l, long long r);
