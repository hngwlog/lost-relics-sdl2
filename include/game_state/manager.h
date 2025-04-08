#pragma once
#include "home_screen.h"
#include "level_select_screen.h"
#include "screen.h"

extern HomeScreen* homeScreen;
extern LevelSelectScreen* levelSelectScreen;
extern Screen* instructionScreen;
extern Screen* optionsScreen;
extern Screen* quitScreen;

int loadHomeScreen();

int loadGame();

int playLevel(int level);

int loadInstruction();

int loadOptions();

int loadQuit();
