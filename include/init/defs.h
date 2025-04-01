#ifndef _DEFS__H
#define _DEFS__H

#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

extern TTF_Font* gFont;

void logErrorAndExit(const char* msg, const char* error);

#endif // _DEFS__H

