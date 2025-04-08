#pragma once
#include "home_screen.h"
#include "level_select_screen.h"
#include "instruction_screen.h"
#include "options_screen.h"
#include "quit_screen.h"

extern HomeScreen* homeScreen;
extern LevelSelectScreen* levelSelectScreen;
extern InstructionScreen* instructionScreen;
extern OptionsScreen* optionsScreen;
extern QuitScreen* quitScreen;

int loadHomeScreen();

int loadGame();

int playLevel(int level);

int loadInstruction();

int loadOptions();

int loadQuit();
