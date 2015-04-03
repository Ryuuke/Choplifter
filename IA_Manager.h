#ifndef IA_MANAGER_H_INCLUDED
#define IA_MANAGER_H_INCLUDED

#include "const.h"
#include "globals.h"
#include "timers.h"
#include "vectorManager.h"
#include "engine_manager.h"
#include "collisionManager.h"
#include "soundManager.h"

// tank
void updateTank(float refreshRate, SDL_Rect *newPosition);
void updateFireTank(float refreshRate, SDL_Rect *newPosition);
void updateCanon();

// otage
void updateOtage(float refreshRate, SDL_Rect *newPosition);

// aircraft
void updateAircraft(float refreshRate, SDL_Rect *newPosition);
void IAircraft(float refreshRate, SDL_Rect *newPosition);
void updateFireAircraft(float refreshRate, SDL_Rect *newPosition);

// explosion
void updateExplosion(float refreshRate, SDL_Rect *newPosition);

// saucer
void updateSaucer(float refreshRate, SDL_Rect *newPosition);
#endif // IA_MANAGER_H_INCLUDED