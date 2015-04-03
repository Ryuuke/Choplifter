#include "collisionManager.h"

bool collisionTank(int *position, SDL_Rect *newPosition, SDL_Rect *oldposition)
{
	Tank *tankNow = listTank->premier;

	while (tankNow != NULL) {
		
		if(tankNow->positionList != *position) // si le tank en question n'est pas celui qui est entrain d'essayer de bouger
		{
			if(newPosition->x > oldposition->x) // si il bouge vers la droite
			{
				if(tankNow->positionWin.x < newPosition->x + TANK_WIDTH && tankNow->positionWin.x + TANK_WIDTH > newPosition->x + TANK_WIDTH) // si il y'a collision vers la droite
					return TRUE;
			}
			else
			{
				if(newPosition->x < tankNow->positionWin.x + TANK_WIDTH && newPosition->x > tankNow->positionWin.x) // si il y'a collision vers la gauche
					return TRUE;
			}
		}

		tankNow = tankNow->suivant;
	}

	return FALSE;
}

void targetFireTank(Fire *fireNow)
{	
	if(helico->positionWin.y + HELICO_HEIGHT >= POSITION_BOTTOM-3)
	{
		if(helico->direction == D_RIGHT)
		{
			if(helico->positionWin.x + HELICO_CENTER <= fireNow->positionWin.x && helico->positionWin.x + HELICO_WIDTH > fireNow->positionWin.x + FIRE_WIDTH)
			{
				if(helico->win == FALSE)	
					helico->isDeath = TRUE;
			}
		}

		if(helico->direction == D_LEFT)
		{
			if(helico->positionWin.x <= fireNow->positionWin.x && helico->positionWin.x + HELICO_WIDTH - HELICO_CENTER > fireNow->positionWin.x + FIRE_WIDTH)
			{
					if(helico->win == FALSE)
					helico->isDeath = TRUE;
			}
		}

		if(helico->direction == D_FORWARD)
		{
			if(helico->positionWin.x <= fireNow->positionWin.x && helico->positionWin.x + HELICO_WIDTH > fireNow->positionWin.x + FIRE_WIDTH)
			{
					if(helico->win == FALSE)
					helico->isDeath = TRUE;
			}
		}
	}

	Otage *otageNow = listOtage->premier;

	while (otageNow != NULL) {
		
		if(otageNow->positionWin.x <= fireNow->positionWin.x && otageNow->positionWin.x + OTAGE_WIDTH > fireNow->positionWin.x + FIRE_WIDTH)
		{	
			destroyOtagePosition(listOtage, otageNow->positionList);
			destroyElementPosition(listFireTank, fireNow->positionList);
		}

		otageNow = otageNow->suivant;
	}

	Prison *prisonNow = listPrison->premier;

	SDL_Rect position, positionOtage;
	DirectionX directionX = direction_left;

	while (prisonNow != NULL) {
		
		if(prisonNow->positionWin.x <= fireNow->positionWin.x&& prisonNow->positionWin.x + PRISON_WIDTH > fireNow->positionWin.x + FIRE_WIDTH)
		{	
			position.x = prisonNow->positionWin.x + prisonNow->positionImage.w /4;
			position.y = prisonNow->positionWin.y;
			
			positionOtage.x = position.x;
			positionOtage.y = POSITION_BOTTOM - OTAGE_HEIGHT;

			createExplosionPrison(&position);
			createOtage(NB_OTAGE_PER_PRISON, &positionOtage, &directionX);
			destroyPrisonPosition(listPrison, prisonNow->positionList);
			destroyElementPosition(listFireTank, fireNow->positionList);
			soundExplosion();
		}

		prisonNow = prisonNow->suivant;
	}
}

void targetFireAircraft(SDL_Rect *positionFire)
{	
	if(helico->direction == D_RIGHT)
	{
		if(helico->positionWin.x + HELICO_CENTER <= positionFire->x && helico->positionWin.x + HELICO_WIDTH > positionFire->x + FIRE_AIRCRAFT_WIDTH && helico->positionWin.y < positionFire->y && helico->positionWin.y + HELICO_HEIGHT > positionFire->y)
		{
			if(helico->win == FALSE)
				helico->isDeath = TRUE;
		}
	}

	if(helico->direction == D_LEFT)
	{
		if(helico->positionWin.x <= positionFire->x && helico->positionWin.x + HELICO_WIDTH - HELICO_CENTER > positionFire->x + FIRE_AIRCRAFT_WIDTH && helico->positionWin.y < positionFire->y && helico->positionWin.y + HELICO_HEIGHT > positionFire->y)
		{
			if(helico->win == FALSE)
				helico->isDeath = TRUE;
		}
	}

	if(helico->direction == D_FORWARD)
	{
		if(helico->positionWin.x <= positionFire->x && helico->positionWin.x + HELICO_WIDTH > positionFire->x + FIRE_AIRCRAFT_WIDTH && helico->positionWin.y < positionFire->y && helico->positionWin.y + HELICO_HEIGHT > positionFire->y)
		{
			if(helico->win == FALSE)
				helico->isDeath = TRUE;
		}
	}
}

void targetFireHelico(Fire *fireNow)
{
	Tank *tankNow = listTank->premier;
	Aircraft *aircraftNow = listAircraft->premier;
	Prison *prisonNow = listPrison->premier;
	Saucer *saucerNow = listSaucer->premier;

	SDL_Rect positionOtage, position;

	DirectionX directionX = direction_left;

	while (tankNow != NULL) 
	{
		if(fireNow->positionWin.x > tankNow->positionWin.x && fireNow->positionWin.x < tankNow->positionWin.x + TANK_WIDTH && fireNow->positionWin.y + FIRE_HEIGHT > tankNow->positionWin.y)
		{
			position.x = tankNow->positionWin.x;
			position.y = tankNow->positionWin.y - 60;

			createExplosion(&position);
			destroyTankPosition(listTank, tankNow->positionList);
			destroyElementPosition(listFireHelico, fireNow->positionList);
			
			soundExplosion();
		}

		tankNow = tankNow->suivant;
	}

	while (aircraftNow != NULL) 
	{
		if(fireNow->positionWin.x > aircraftNow->positionWin.x && fireNow->positionWin.x < aircraftNow->positionWin.x + aircraftNow->positionImage.w && fireNow->positionWin.y + FIRE_HEIGHT > aircraftNow->positionWin.y && fireNow->positionWin.y < aircraftNow->positionWin.y + aircraftNow->positionImage.h)
		{
			position.x = aircraftNow->positionWin.x;
			position.y = aircraftNow->positionWin.y - 60;
			
			createExplosion(&position);
			destroyAircraftPosition(listAircraft, aircraftNow->positionList);
			destroyElementPosition(listFireHelico, fireNow->positionList);
			soundExplosion();
		}
		
		aircraftNow = aircraftNow->suivant;
	}

	while (saucerNow != NULL) 
	{
		if(fireNow->positionWin.x > saucerNow->positionWin.x && fireNow->positionWin.x < saucerNow->positionWin.x + saucerNow->positionImage.w && fireNow->positionWin.y + FIRE_HEIGHT > saucerNow->positionWin.y && fireNow->positionWin.y < saucerNow->positionWin.y + saucerNow->positionImage.h)
		{
			position.x = saucerNow->positionWin.x;
			position.y = saucerNow->positionWin.y - 31;

			createExplosion(&position);
			destroySaucerPosition(listSaucer, saucerNow->positionList);
			destroyElementPosition(listFireHelico, fireNow->positionList);
			soundExplosion();
		}
		
	 	saucerNow = saucerNow->suivant;
	}

	while (prisonNow != NULL) 
	{
		if(fireNow->positionWin.x > prisonNow->positionWin.x && fireNow->positionWin.x < prisonNow->positionWin.x + prisonNow->positionImage.w && fireNow->positionWin.y + FIRE_HEIGHT > prisonNow->positionWin.y && fireNow->positionWin.y < prisonNow->positionWin.y + prisonNow->positionImage.h)
		{
			SDL_Rect position;

			position.x = prisonNow->positionWin.x + prisonNow->positionImage.w /4;
			position.y = prisonNow->positionWin.y;
			
			positionOtage.x = position.x;
			positionOtage.y = POSITION_BOTTOM - OTAGE_HEIGHT;

			createExplosionPrison(&position);
			createOtage(NB_OTAGE_PER_PRISON, &positionOtage, &directionX);
			destroyPrisonPosition(listPrison, prisonNow->positionList);
			destroyElementPosition(listFireHelico, fireNow->positionList);
			soundExplosion();
		}
		
		prisonNow = prisonNow->suivant;
	}
}

bool collisionSaucer(Saucer *saucerNow)
{
	SDL_Rect position;
	position.x = 0; position.y = 0;

	if(saucerNow->positionWin.x > helico->positionWin.x && saucerNow->positionWin.x < helico->positionWin.x + helico->positionImage.w && saucerNow->positionWin.y + SAUCER_HEIGHT > helico->positionWin.y && saucerNow->positionWin.y < helico->positionWin.y + HELICO_HEIGHT)
	{
		position.x = saucerNow->positionWin.x - 50;
		position.y = saucerNow->positionWin.y - 60;

		destroySaucerPosition(listSaucer, saucerNow->positionList);
		createExplosion(&position);
		soundExplosion();
		
		if(helico->win == FALSE)
			helico->isDeath = TRUE;

		return TRUE;
	}

	if(helico->positionWin.x + HELICO_CENTER_X > saucerNow->positionWin.x && helico->positionWin.x < saucerNow->positionWin.x + saucerNow->positionImage.w && helico->positionWin.y + HELICO_HEIGHT > saucerNow->positionWin.y && helico->positionWin.y < saucerNow->positionWin.y + SAUCER_HEIGHT)
	{
		position.x = saucerNow->positionWin.x + 50;
		position.y = saucerNow->positionWin.y - 60;

		destroySaucerPosition(listSaucer, saucerNow->positionList);
		createExplosion(&position);
		soundExplosion();

		if(helico->win == FALSE)
			helico->isDeath = TRUE;

		return TRUE;
	}

	return FALSE;
}