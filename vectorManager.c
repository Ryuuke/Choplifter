#include "vectorManager.h"


Vector* normalize(Vector *vector)
{
	float lenght = sqrt( vector->x * vector->x + vector->y * vector->y);
    
	vector->x = vector->x/lenght;
	vector->y = vector->y/lenght;

	return vector;
}

Vector direction(SDL_Rect src, SDL_Rect target)
{
	Vector vector;

	vector.x = target.x - src.x;
	vector.y = target.y - src.y;

	return vector;
}