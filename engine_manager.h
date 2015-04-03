#ifndef LISTE_CHAINEE_H_INCLUDED
#define LISTE_CHAINEE_H_INCLUDED

#include <SDL/SDL.h>
#include <stdlib.h>
#include "globals.h"

// fire

ListeFire* initialisation();
Fire* lastElement(ListeFire *liste);
Fire* returnElementPosition(ListeFire *liste, int position);
void addElementFirst(ListeFire *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, Vector *vector);
void addElementLast(ListeFire *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, Vector *vector);
void destroyElementPosition(ListeFire *liste, int position);
void *destroyElementList(ListeFire *liste);

// otage

ListeOtage* initialisationOtage();
void addOtageFirst(ListeOtage *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, DirectionX *direction);
void addOtageLast(ListeOtage *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, DirectionX *direction);
Otage* lastOtage(ListeOtage *liste);
Otage* returnOtagePosition(ListeOtage *liste, int positionList);
void destroyOtagePosition(ListeOtage *liste, int position);
void *destroyOtageList(ListeOtage *liste);

// aircraft

ListeAircraft* initialisationAircraft();
void addAircraftFirst(ListeAircraft *liste, SDL_Rect *positionWin, DirectionX *directionX);
void addAircraftLast(ListeAircraft *liste, SDL_Rect *positionWin, DirectionX *directionX);
Aircraft* lastAircraft(ListeAircraft *liste);
Aircraft* returnAircraftPosition(ListeAircraft *liste, int positionList);
void destroyAircraftPosition(ListeAircraft *liste, int position);
void *destroyAircraftList(ListeAircraft *liste);

// tank

ListeTank* initialisationTank();
void addTankFirst(ListeTank *liste, int positionX);
void addTankLast(ListeTank *liste, int positionX);
Tank* lastTank(ListeTank *liste);
Tank* returnTankPosition(ListeTank *liste, int positionList);
void destroyTankPosition(ListeTank *liste, int position);
void *destroyTankList(ListeTank *liste);

// Explosion

ListeExplosion* initialisationExplosion();
void addExplosionFirst(ListeExplosion *liste, SDL_Rect *positionWin, SDL_Rect *positionImage);
void addExplosionLast(ListeExplosion *liste, SDL_Rect *positionWin, SDL_Rect *positionImage);
Explosion* lastExplosion(ListeExplosion *liste);
Explosion* returnExplosionPosition(ListeExplosion *liste, int positionList);
void destroyExplosionPosition(ListeExplosion *liste, int position);
void *destroyExplosionList(ListeExplosion *liste);

// Prison

ListePrison* initialisationPrison();
void addPrisonFirst(ListePrison *liste, SDL_Rect *positionWin, SDL_Rect *positionImage);
void addPrisonLast(ListePrison *liste, SDL_Rect *positionWin, SDL_Rect *positionImage);
Prison* lastPrison(ListePrison *liste);
Prison* returnPrisonPosition(ListePrison *liste, int positionList);
void destroyPrisonPosition(ListePrison *liste, int position);
void *destroyPrisonList(ListePrison *liste);

// saucer

ListeSaucer* initialisationSaucer();
void addSaucerFirst(ListeSaucer *liste, SDL_Rect *positionWin, DirectionX *directionX);
void addSaucerLast(ListeSaucer *liste, SDL_Rect *positionWin, DirectionX *directionX);
Saucer* lastSaucer(ListeSaucer *liste);
Saucer* returnSaucerPosition(ListeSaucer *liste, int positionList);
void destroySaucerPosition(ListeSaucer *liste, int position);
void *destroySaucerList(ListeSaucer *liste);

#endif // LISTE_CHAINEE_H_INCLUDED