#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL_Image.h>
#include "timers.h"
#include "globals.h"
#include "const.h"
#include "engine_manager.h"
#include "vectorManager.h"
#include "soundManager.h"
#include "initialize.h"
#include "textManager.h"
#include "IA_Manager.h"

void game();
void play();
// void displayMenu();
void event(Input *keyPad);
void update(Input *keyPad);

void updateHelico(Input *keyPad, float refreshRate, SDL_Rect *newPosition);
void updateBackground(Input *keyPad, float refreshRate, SDL_Rect *newPosition);
void updateBalleHelico(Input *keyPad, float refreshRate, SDL_Rect *newPosition);
void updatePositionOnBackground(float refreshRate, float oldPosition, float newPosition);
void world();
void theEnd();

#endif // GAME_H_INCLUDED