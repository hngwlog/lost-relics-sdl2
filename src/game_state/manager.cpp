#include <SDL.h>
#include "../../include/init/defs.h"
#include "../../include/init/timer.h"
#include "../../include/game_state/manager.h"
#include "../../include/game_state/play.h"

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
            state = playLevel(state);
            if (state == - 2) {
                delete levelSelectScreen;

                return HOME;
            }
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

    selectSound->stop();
    gameMusic->play();

    Game* game = new Game();
    game->init(level);

    bool quit = false;
    SDL_Event event;

    /** The frames per second timer */
    Timer fpsTimer;

    /** The frames per second cap timer */
    Timer capTimer;

    /** Start counting frames per second */
    fpsTimer.start();

    int startTime = 0, currentTime, deltaTime;

    int state = 0;

    while (!quit) {

        /** Start cap timer */
        capTimer.start();
        currentTime = fpsTimer.getTicks();

        deltaTime = std::min(currentTime - startTime, SCREEN_TICKS_PER_FRAME);
        startTime = currentTime;

        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;

                gameMusic->stop();

                return QUIT;
            }
            else if ((state == 0 || state == - 2) && event.type == SDL_KEYDOWN) {
                if (state == 0 && event.key.keysym.sym == SDLK_ESCAPE) state = - 2;
                else if (state == - 2 && event.key.keysym.sym == SDLK_RETURN) state = 0;
            }
        }

        if (state == 0) game->update(deltaTime);

        if (state == - 2) game->renderPause();
        else {
            state = game->getGameState();
            if (state < 0) {
                gameMusic->stop();
                loseSound->play(0);

                int score = game->renderLose();
                score = 0;
                levelSelectScreen->levels[level].score = std::max(levelSelectScreen->levels[level].score, score);
                const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
                if (currentKeyState[SDL_SCANCODE_R]) {
                    delete game;

                    return - 1;
                }
                else if (currentKeyState[SDL_SCANCODE_H]) {
                    delete game;

                    return - 2;
                }
            }
            else if (state == 0) game->render();
            else {
                gameMusic->stop();
                winSound->play(0);

                int score = game->renderWin();
                levelSelectScreen->levels[level].score = std::max(levelSelectScreen->levels[level].score, score);
                levelSelectScreen->unlockLevel(level);
                const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);
                if (currentKeyState[SDL_SCANCODE_R]) {
                    delete game;

                    return - 1;
                }
                else if (currentKeyState[SDL_SCANCODE_H]) {
                    delete game;

                    return - 2;
                }
            }
        }

        SDL_RenderPresent(gRenderer);

        /** If frame finished early */
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            /** Wait remaining time */
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }

    delete game;

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
                selectSound->play(0);

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
                selectSound->play(0);

                quit = true;
                return QUIT;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_y) {
                    selectSound->play(0);

                    delete quitScreen;

                    return - 1;
                }
                if (event.key.keysym.sym == SDLK_n) {
                    selectSound->play(0);

                    delete quitScreen;

                    return HOME;
                }
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

