#include "../../include/init/defs.h"

SDL_Renderer* gRenderer;
SDL_Window* gWindow;

TTF_Font* gFont;

MusicManager *gameMusic, *jumpSound, *coinSound, *dashSound, *attackSound, *selectSound, *hitEnemySound, *loseSound, *winSound;

void logErrorAndExit(const char* msg, const char* error) {

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}
