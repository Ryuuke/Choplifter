#ifndef INITIALIZE_H_INCLUDED
#define INITIALIZE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL_Image.h>
#include "globals.h"
#include "const.h"
#include "engine_manager.h"
#include "IA_Manager.h"
#include "SDL_ttf.h"
#include "timers.h"

//	init
void initWindow();
void initSounds();
void initTexts();
void initAll();
void replay();

void initStage();
void deleteStage();

//	create engine
void createOtage(int nbr_otage, SDL_Rect *otagePositionWin, DirectionX *direction);
void createExplosion(SDL_Rect *explosionPositionWin);
void createExplosionPrison(SDL_Rect *explosionPositionWin);
void createPrison();

//	blit
void blitAll();
void blit(SDL_Surface *src, SDL_Rect *posImg, SDL_Rect *posWin);

// delete
void quit();
void deleteSurface();
void deleteLists();
void deleteSound();
void deleteTexts();

#endif // INITIALIZE_H_INCLUDED