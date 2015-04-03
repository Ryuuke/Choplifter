#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include <stdlib.h>
#include <SDL/SDL.h>
#include "globals.h"
#include "const.h"
#include "engine_manager.h"
#include "initialize.h"
#include "soundManager.h"

bool collisionTank(int *position, SDL_Rect *newPosition, SDL_Rect *oldposition);
void targetFireTank(Fire *fireNow);
void targetFireAircraft(SDL_Rect *positionFire);
void targetFireHelico(Fire *fireNow);
bool collisionSaucer(Saucer *saucerNow);

#endif // COLLISIONMANAGER_H_INCLUDED