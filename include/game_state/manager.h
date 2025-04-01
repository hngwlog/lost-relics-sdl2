#pragma once
#include "home_screen.h"
#include "instruction_screen.h"
#include "quit_screen.h"

extern HomeScreen* homeScreen;
extern InstructionScreen* instructionScreen;
extern QuitScreen* quitScreen;

int loadHomeScreen();

int loadGame();

int loadInstruction();

int loadOptions();

int loadQuit();
