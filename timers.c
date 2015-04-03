#include "timers.h"

void initTimers()
{
	previousTime              = SDL_GetTicks();
	previousTimeSpawnTank     = SDL_GetTicks();
	previousTimeSpawnAircraft = SDL_GetTicks();
	previousTimespawnOtage    = SDL_GetTicks();
	previousTimeSoundHelico   = SDL_GetTicks();
	previousTimeTurnOtage     = SDL_GetTicks();
}

float myRefresh()
{
	Uint32 currentTime = SDL_GetTicks();
	float timeBetweenRefresh = 0.f;

	timeBetweenRefresh = currentTime - previousTime;
	previousTime = currentTime;

	return timeBetweenRefresh; 
}

int timeAllowed(Uint32 *previous, Uint32 timePassed) // prend en parametre une variable et un temps
{
	Uint32 currentTime = SDL_GetTicks();

	if(currentTime - *previous > timePassed) // si timePassed est ecoulé on change la valeur de previous et on retourne TRUE
	{
		*previous = currentTime;
		
		return TRUE;
	}

	return FALSE;
}

void animHelico(Input *keypad)
{
	if(timeAllowed(&helico->previousTimeAnimation, TEMP_ANIMATION_HELICO)) // chaque 40 ms
	{
		if(helico->direction == D_LEFT) // si la direction de l'helico est GAUCHE
		{
			helico->positionFire = FIRE_LEFT; // on change la position initiales des balle de l'elico (le canon si on peu dire sa comme sa)
			
			if(helico->positionImage.x >= HELICO_IMAGE_MAX) // on change son image
				helico->positionImage.x = HELICO_POSITION_RIGHT_X;
			else
				helico->positionImage.x += HELICO_WIDTH;
		}
		
		if(helico->direction == D_RIGHT)
		{
			helico->positionFire = FIRE_RIGHT;

			if(helico->positionImage.x >= (HELICO_POSITION_LEFT_X + HELICO_IMAGE_MAX))
				helico->positionImage.x = HELICO_POSITION_LEFT_X;
			else
				helico->positionImage.x += HELICO_WIDTH;
		}
		
		if(helico->direction == D_FORWARD)
		{
			helico->positionFire = FIRE_FORWARD;
			
			if(helico->positionImage.x >= (HELICO_POSITION_FORWARD_X + HELICO_IMAGE_MAX))
				helico->positionImage.x = HELICO_POSITION_FORWARD_X;
			else
				helico->positionImage.x += HELICO_WIDTH;
		}
	}
}

void gravity(Input *keypad, float refreshRate)
{
	if(keypad->key[UP] == FALSE && keypad->key[DOWN] == FALSE) // si l'helico de dessend pas et ne monte pas
	{
		if(helico->positionWin.y + HELICO_HEIGHT+1 < POSITION_BOTTOM && timeAllowed(&helico->previousTimegravity, TEMP_ANIMATION_GRAVITY)) // si l'helico vole & que 100ms sont passé apres la derniere animation
		{
			helico->positionWin.y += (refreshRate * GRAVITY); // on l'atire vers le bas
		}
	}
}

void animOtage()
{
	Otage *otageNow = listOtage->premier;

	while(otageNow != NULL)
	{
		if(timeAllowed(&otageNow->previousTimeAnimation, TEMP_ANIMATION_OTAGE))
		{
			if(otageNow->direction == direction_left)
			{
				otageNow->positionImage.y = OTAGE_POSITION_LEFT_Y;

				if(otageNow->positionImage.x >= OTAGE_IMAGE_MAX)
					otageNow->positionImage.x = OTAGE_POSITION_X;
				else
					otageNow->positionImage.x += OTAGE_WIDTH + PX_ENTRE_OTAGE_IMAGE;
			}
			else
			{
				otageNow->positionImage.y = OTAGE_POSITION_RIGHT_Y;

				if(otageNow->positionImage.x >= OTAGE_IMAGE_MAX)
					otageNow->positionImage.x = OTAGE_POSITION_X;
				else
					otageNow->positionImage.x += OTAGE_WIDTH + PX_ENTRE_OTAGE_IMAGE;
			}
		}

		otageNow = otageNow->suivant;
	}

	if(timeAllowed(&previousTimeTurnOtage, TIME_TURN_OTAGE))
	{
		if(timePassedOtageTurn == TRUE)
			timePassedOtageTurn = FALSE;
		else
			timePassedOtageTurn = TRUE;
	}
		
	
}

void animAircraft(Aircraft *aircraftNow, float refreshRate, SDL_Rect *newPosition)
{
	if(timeAllowed(&aircraftNow->previousTimeAnimation, TEMP_ANIMATION_AIRCRAFT)) // si 100 ms se sont écoulé
	{
		if(aircraftNow->directionY == direction_top) // si la direction de l'avion est vers le haut
		{
			aircraftNow->positionWin.y -= (int) (refreshRate * VITESS_AIRCRAFT_Y); // on la monte

			if(aircraftNow->positionWin.y <= aircraftNow->oldPositionY-DISTANCE_AIRCRAFT_Y) // si elle atteind un certain taux de hauteur on change sa direction vers le bas
				aircraftNow->directionY = direction_bot;
		}
		else
		{
			aircraftNow->positionWin.y += (int) (refreshRate * VITESS_AIRCRAFT_Y);
			
			if(aircraftNow->positionWin.y >= aircraftNow->oldPositionY+DISTANCE_AIRCRAFT_Y)
			{
				aircraftNow->directionY = direction_top;
			}
		}
	}
}

void directionAircraft()
{
	Aircraft *aircraftNow = listAircraft->premier;

	while (aircraftNow != NULL) 
	{	
		if(aircraftNow->directionX == direction_left)
		{
			aircraftNow->positionImage.y = AIRCRAFT_POSITION_LEFT_Y;
		}
		else
		{
			aircraftNow->positionImage.y = AIRCRAFT_POSITION_RIGHT_Y;
		}

		aircraftNow = aircraftNow->suivant;
	}
}

void animExplosion(Explosion *explosion)
{
	if(timeAllowed(&explosion->previousTimeAnimation, TEMP_ANIMATION_EXPLOSION))
	{
		if(explosion->positionImage.x >= EXPLOSION_IMAGE_MAX)
			destroyExplosionPosition(listExplosion, explosion->positionList);

		explosion->positionImage.x += EXPLOSION_WIDTH;
	}
}

void animExplosionPrison(Explosion *explosion)
{
	if(timeAllowed(&explosion->previousTimeAnimation, TEMP_ANIMATION_EXPLOSION_PRISON))
	{
		if(explosion->positionImage.x >= EXPLOSION_PRISON_IMAGE_MAX)
			destroyExplosionPosition(listExplosion, explosion->positionList);

		explosion->positionImage.x += EXPLOSION_PRISON_WIDTH;
	}
}

void animFireAircraft(Fire *fireNow)
{
	if(fireNow->vector.x == 1)
		fireNow->positionImage.x = FIRE_RIGHT_AIRCRAFT_POSITION_X;
	else
		fireNow->positionImage.x = FIRE_LEFT_AIRCRAFT_POSITION_X;
}

void animFire(Fire *fireNow)
{
	if(timeAllowed(&fireNow->previousTimeAnimation, 3))
	{
		if(fireNow->positionImage.y == FIRE_POSITION_Y)
			fireNow->positionImage.y = 253;
		else
			fireNow->positionImage.y = 241;
	}
}

void animSaucer(Saucer *saucer)
{
	if(timeAllowed(&saucer->previousTimeAnimation, TEMP_ANIMATION_SAUCER))
	{
		if(saucer->positionImage.x >= SAUCER_IMG_MAX)
			saucer->positionImage.x = SAUCER_POSITION_X;
		else
			saucer->positionImage.x += SAUCER_WIDTH + DISTANCE_SAUCER_X;
	}
}