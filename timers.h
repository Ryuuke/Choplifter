#ifndef TIMERS_H_INCLUDED
#define TIMERS_H_INCLUDED

#include "SDL/SDL.h"
#include "globals.h"
#include "const.h"
#include "engine_manager.h"

void initTimers();
float myRefresh();
int timeAllowed(Uint32 *previous, Uint32 timePassed);

void animHelico(Input *keypad);
void gravity(Input *keypad, float refreshRate);

void animExplosion(Explosion *explosion);
void animExplosionPrison(Explosion *explosion);

void animOtage();

void animAircraft(Aircraft *aircraftNow, float refreshRate, SDL_Rect *newPosition);
void directionAircraft();
void animFireAircraft(Fire *fireNow);
void animFire(Fire *fireNow);
void animSaucer(Saucer *saucer);

#endif // TIMERS_H_INCLUDED