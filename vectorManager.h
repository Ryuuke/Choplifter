#ifndef VECTORMANAGER_H_INCLUDED
#define VECTORMANAGER_H_INCLUDED

#include <math.h>
#include "globals.h"

Vector* normalize(Vector *vector);
Vector direction(SDL_Rect src, SDL_Rect target);

#endif // VECTORMANAGER_H_INCLUDED