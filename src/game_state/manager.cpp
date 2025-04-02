#include <SDL.h>
#include "../../include/init/defs.h"
#include "../../include/init/timer.h"
#include "../../include/game_state/manager.h"

HomeScreen* homeScreen;
LevelSelectScreen* levelSelectScreen;
InstructionScreen* instructionScreen;
QuitScreen* quitScreen;

int loadHomeScreen() {

    homeScreen = new HomeScreen();
    homeScreen->init();

    bool quit = false;
    SDL_Event event;

    int state = - 1;

    /** The frames per second timer */
    Timer fpsTimer;

    /** The frames per second cap timer */
    Timer capTimer;

    /** Start counting frames per second */
    fpsTimer.start();

    int startTime = 0, currentTime, deltaTime;

    while (!quit) {
        /** Start cap timer */
        capTimer.start();
        currentTime = fpsTimer.getTicks();

        deltaTime = std::min(currentTime - startTime, SCREEN_TICKS_PER_FRAME);
        startTime = currentTime;

        state = homeScreen->update(deltaTime);

        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                return QUIT;
            }
        }

        if (state == - 1) homeScreen->render();
        else {
            delete homeScreen;

            return state;
        }

        SDL_RenderPresent(gRenderer);

        /** If frame finished early */
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            /** Wait remaining time */
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    delete homeScreen;

    return - 1;
}

int loadGame() {

    levelSelectScreen = new LevelSelectScreen();
    levelSelectScreen->init(5);

    bool quit = false;
    SDL_Event event;

    int state = - 1;

    /** The frames per second timer */
    Timer fpsTimer;

    /** The frames per second cap timer */
    Timer capTimer;

    /** Start counting frames per second */
    fpsTimer.start();

    int startTime = 0, currentTime, deltaTime;

    while (!quit) {
        /** Start cap timer */
        capTimer.start();
        currentTime = fpsTimer.getTicks();

        deltaTime = std::min(currentTime - startTime, SCREEN_TICKS_PER_FRAME);
        startTime = currentTime;

        state = levelSelectScreen->update(deltaTime);

        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                return QUIT;
            }
        }

        if (state == - 2) {
            delete levelSelectScreen;

            return HOME;
        }
        else if (state == - 1) levelSelectScreen->render();
        else {
            playLevel(state);
            state = - 1;
        }

        SDL_RenderPresent(gRenderer);

        /** If frame finished early */
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            /** Wait remaining time */
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    delete levelSelectScreen;

    return - 1;
}

int playLevel(int level) {

    return - 1;
}

int loadInstruction() {

    instructionScreen = new InstructionScreen();
    instructionScreen->init();

    bool quit = false;
    SDL_Event event;

    /** The frames per second timer */
    Timer fpsTimer;

    /** The frames per second cap timer */
    Timer capTimer;

    /** Start counting frames per second */
    fpsTimer.start();

    while (!quit) {
        /** Start cap timer */
        capTimer.start();

        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                return QUIT;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                delete instructionScreen;

                return HOME;
            }
        }

        instructionScreen->render();

        SDL_RenderPresent(gRenderer);

        /** If frame finished early */
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            /** Wait remaining time */
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    delete instructionScreen;

    return - 1;
}

int loadOptions() {

    return - 1;
}

int loadQuit() {

    quitScreen = new QuitScreen();
    quitScreen->init();

    bool quit = false;
    SDL_Event event;

    /** The frames per second timer */
    Timer fpsTimer;

    /** The frames per second cap timer */
    Timer capTimer;

    /** Start counting frames per second */
    fpsTimer.start();

    while (!quit) {
        /** Start cap timer */
        capTimer.start();

        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                return QUIT;
            }
            else if (event.type == SDL_KEYDOWN) {

                delete quitScreen;

                if (event.key.keysym.sym == SDLK_y) return - 1;
                if (event.key.keysym.sym == SDLK_n) return HOME;
            }
        }

        quitScreen->render();

        SDL_RenderPresent(gRenderer);

        /** If frame finished early */
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            /** Wait remaining time */
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    delete quitScreen;

    return - 1;
}

