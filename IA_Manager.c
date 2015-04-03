#include "IA_Manager.h"


void updateTank(float refreshRate, SDL_Rect *newPosition)
{
	Tank *tankNow = listTank->premier;

	while (tankNow != NULL)
	{	
		newPosition->x = tankNow->positionWin.x;
		newPosition->y = tankNow->positionWin.y;

		if(tankNow->positionWin.x - helico->positionWin.x > POSITION_CANNON_CENTER-2) // si le tank est a droite de l'helico, il vire a gauche
		{
			newPosition->x -= (int) (refreshRate * VITESS_TANK);
		}
		else if(tankNow->positionWin.x - helico->positionWin.x < POSITION_CANNON_CENTER-2) // si le tank est a gauche de l'helico, il vire a droite
		{
			newPosition->x += (int) (refreshRate * VITESS_TANK);
		}

		if(collisionTank(&tankNow->positionList, newPosition, &tankNow->positionWin) == FALSE)
		{
			tankNow->positionWin.x = newPosition->x;
		}

		tankNow = tankNow->suivant;
	}

	updateCanon(); // on change la position initiale de la balle et de l'image du tank
	updateFireTank(refreshRate, newPosition); // si on peu tirer, bah.. on tire :D
}

void updateFireTank(float refreshRate, SDL_Rect *newPosition)
{
	Tank *tankNow = listTank->premier;

	while (tankNow != NULL) {
		
		if((helico->positionWin.x - tankNow->positionWin.x < DISTANCE_TANK_FIRE_RIGHT ^ tankNow->positionWin.x - helico->positionWin.x > DISTANCE_TANK_FIRE_LEFT) && timeAllowed(&tankNow->previousTimeFire, TIME_FIRE_TANK) && helico->isDeath == FALSE)
		{
			SDL_Rect firePositionWin;
			SDL_Rect firePositionImage;
			Vector vector;

			SDL_Rect tankPos, helicoPos;

			// on prend la position du tank dans la fenetre
			tankPos.x = tankNow->positionWin.x; 
			tankPos.y = tankNow->positionWin.y + tankNow->positionCanon;

			// on prend la position de l'helico dans la fenetre
			helicoPos.x = helico->positionWin.x + tankNow->positionCanon;
			helicoPos.y = helico->positionWin.y + HELICO_CENTER_Y;

			// position initial de la balle	
			firePositionWin.x = tankNow->positionWin.x + tankNow->positionCanon; 
			firePositionWin.y = tankNow->positionWin.y;

			firePositionImage.x = FIRE_POSITION_X;
			firePositionImage.y = FIRE_POSITION_Y;
			firePositionImage.w = FIRE_WIDTH;
			firePositionImage.h = FIRE_HEIGHT;

			// focus vers l'elico
			vector = direction(tankPos, helicoPos);
			
			soundFireTank();
			addElementLast(listFireTank, &firePositionWin, &firePositionImage, normalize(&vector)); // ajout de la balle + son vecteur dans la liste
		}

		tankNow = tankNow->suivant;
	}
	
	Fire *fireNow = listFireTank->premier;
	
	while (fireNow != NULL ) // pour chaque balle dans la liste fireTank
	{
		if(fireNow->positionWin.y <= 320 && fireNow->vector.y < 0) // si la balle est entrain de monter, et elle depasse 320
		{
			fireNow->vector.y =  0.5; // changement de la direction de la balle (vers le bas)
		}
		
		newPosition->x = fireNow->positionWin.x + (fireNow->vector.x * refreshRate * FIRE_SPEED_TANK); // mise à jour horizontal de la position de la balle			
		newPosition->y = fireNow->positionWin.y + (fireNow->vector.y * refreshRate * FIRE_SPEED_TANK); // mise à jour vertical de la position de la balle

		if(fireNow->vector.y > 0)
		{
			targetFireTank(fireNow); // si on a toucher l'elico ou l'otage
		}

		if((newPosition->y >= POSITION_BOTTOM && fireNow->vector.y > 0) || newPosition->x <= 0 || newPosition->x + FIRE_WIDTH > SCREEN_WIDTH)	// si y'a eu une collision
		{
			destroyElementPosition(listFireTank, fireNow->positionList); // on l'efface du tableau
		}
		else
		{
			fireNow->positionWin.x = newPosition->x;
			fireNow->positionWin.y = newPosition->y;
		}

		animFire(fireNow);

		fireNow = fireNow->suivant;
	}
}

void updateCanon()
{
	Tank *tankNow = listTank->premier;

	while(tankNow != NULL)
	{
		// positionTank de gauche à droite

		if(helico->positionWin.x -  tankNow->positionWin.x  > 200)
		{
			tankNow->positionCanon = 55;
			tankNow->positionImage.x = 382;
		}
		else if(helico->positionWin.x -  tankNow->positionWin.x  < 200 && helico->positionWin.x -  tankNow->positionWin.x  > 150)
		{
			tankNow->positionCanon = 40;
			tankNow->positionImage.x = 320;
		}
		else if(helico->positionWin.x -  tankNow->positionWin.x  < 150 && helico->positionWin.x -  tankNow->positionWin.x  > 50)
		{
			tankNow->positionCanon = 35;
			tankNow->positionImage.x = 256;
		}
		else if(helico->positionWin.x -  tankNow->positionWin.x  < 50 && helico->positionWin.x -  tankNow->positionWin.x  > 0)
		{
			tankNow->positionCanon = 28;
			tankNow->positionImage.x = 192;
		}

		// position Canon de droite à gauche
		else if(tankNow->positionWin.x - helico->positionWin.x > 200)
		{
			tankNow->positionCanon = 3;
			tankNow->positionImage.x = 0;
		}
		else if(tankNow->positionWin.x - helico->positionWin.x < 200 && tankNow->positionWin.x - helico->positionWin.x > 150)
		{
			tankNow->positionCanon = 15;
			tankNow->positionImage.x = 64;
		}
		else if(tankNow->positionWin.x - helico->positionWin.x  < 150 && tankNow->positionWin.x - helico->positionWin.x  > 50)
		{
			tankNow->positionCanon = 20;
			tankNow->positionImage.x = 128;
		}
		else if(tankNow->positionWin.x - helico->positionWin.x < 50 && tankNow->positionWin.x - helico->positionWin.x  > 0)
		{
			tankNow->positionCanon = 28;
			tankNow->positionImage.x = 192;
		}

		tankNow = tankNow->suivant;
	}
}

void updateOtage(float refreshRate, SDL_Rect *newPosition)
{
	Otage *otageNow = listOtage->premier;

	while (otageNow != NULL) 
	{
		if(helico->positionWin.y + HELICO_HEIGHT > POSITION_BOTTOM-3 && helico->positionWin.x > POSITION_MIN_SPAWN_TANK - backgroundPositionImage.x && (otageNow->positionWin.x > 450 - backgroundPositionImage.x || otageNow->positionWin.x < 100 - backgroundPositionImage.x) && helico->otage < NB_OTAGE_PER_PRISON && helico->isDeath == FALSE)
		{
			if(helico->positionWin.x > otageNow->positionWin.x)
			{
				otageNow->positionWin.x += (int) (refreshRate * VITESS_OTAGE);

				otageNow->direction = direction_right;
		
				if (helico->positionWin.x - otageNow->positionWin.x < 10 )
				{
					destroyOtagePosition(listOtage, otageNow->positionList);
					helico->otage += 1;
				}
			}
			else
			{
				otageNow->positionWin.x -= (int) (refreshRate * VITESS_OTAGE);
				
				otageNow->direction = direction_left;

				if (otageNow->positionWin.x - helico->positionWin.x < 10)
				{
					destroyOtagePosition(listOtage, otageNow->positionList);
					helico->otage += 1;
				}
			}
		}
		else if(otageNow->positionWin.x < POSITION_SAVE_OTAGE - backgroundPositionImage.x)
		{
			otageNow->positionWin.x -= (int) (refreshRate * VITESS_OTAGE);
			otageNow->direction = direction_left;

			if(otageNow->positionWin.x <= 186 - OTAGE_WIDTH - backgroundPositionImage.x && otageNow->positionWin.x >= 100 + OTAGE_WIDTH - backgroundPositionImage.x)
			{
				destroyOtagePosition(listOtage, otageNow->positionList);
			}
		}
		else
		{	
			
			if(timePassedOtageTurn == TRUE)
			{
				otageNow->positionWin.x += (int) (refreshRate * VITESS_OTAGE);
				otageNow->direction = direction_right;
			}
			else
			{
				otageNow->positionWin.x -= (int) (refreshRate * VITESS_OTAGE);
				otageNow->direction = direction_left;
			}
		}
		
		otageNow = otageNow->suivant;
	}

	if(helico->positionWin.y + helico->positionImage.h >= POSITION_BOTTOM-5 && helico->positionWin.x < POSITION_SAVE_OTAGE - backgroundPositionImage.x && helico->positionWin.x > 190 -backgroundPositionImage.x && helico->otage > 0 && timeAllowed(&previousTimespawnOtage, TIME_SPAWN_OTAGE) && helico->isDeath == FALSE)
	{
		DirectionX direction = direction_left;
		SDL_Rect otagePositionWin;

		otagePositionWin.x = helico->positionWin.x;
		otagePositionWin.y = POSITION_BOTTOM - OTAGE_HEIGHT;

		createOtage(1, &otagePositionWin, &direction);

		helico->otage--;
		helico->otageSuccoured++;
	}

	animOtage();
}

void updateAircraft(float refreshRate, SDL_Rect *newPosition)
{
	IAircraft(refreshRate, newPosition);
	directionAircraft();
	updateFireAircraft(refreshRate, newPosition);
}

void IAircraft(float refreshRate, SDL_Rect *newPosition)
{
	Aircraft *aircraftNow = listAircraft->premier;

	while (aircraftNow != NULL) 
	{
		if (aircraftNow->directionX == direction_left)
		{
			aircraftNow->positionWin.x -= (int) (refreshRate * VITESS_AIRCRAFT);

			if((aircraftNow->positionWin.x + aircraftNow->positionImage.w) <= -DISTANCE_SPAWN_AIRCRAFT)
			{
				aircraftNow->directionX = direction_right;
				
				if(helico->positionWin.y < 200 && helico->positionWin.y > 25)
				{	
					aircraftNow->positionWin.y = helico->positionWin.y;
					aircraftNow->oldPositionY = aircraftNow->positionWin.y;
				}
			}
		}
		else
		{
			aircraftNow->positionWin.x += (int) (refreshRate * VITESS_AIRCRAFT);

			if(aircraftNow->positionWin.x + aircraftNow->positionImage.w >= SCREEN_WIDTH + DISTANCE_SPAWN_AIRCRAFT)
			{
				aircraftNow->directionX = direction_left;
				
				if(helico->positionWin.y < 200 && helico->positionWin.y > 25)
				{
					aircraftNow->positionWin.y = helico->positionWin.y;
					aircraftNow->oldPositionY = aircraftNow->positionWin.y;		
				}
			}
		}

		animAircraft(aircraftNow, refreshRate, newPosition);

		aircraftNow = aircraftNow->suivant;
	}
}

void updateFireAircraft(float refreshRate, SDL_Rect *newPosition)
{
	Aircraft *aircraftNow = listAircraft->premier;

	while (aircraftNow != NULL) 
	{
		if(timeAllowed(&aircraftNow->previousTimeFire, TIME_FIRE_AIRCRAFT) && aircraftNow->positionWin.x >= 0 && aircraftNow->positionWin.x + aircraftNow->positionImage.w < SCREEN_WIDTH)
		{
			SDL_Rect firePositionWin;
			SDL_Rect firePositionImage;
			Vector vector;

			SDL_Rect aircraftPos, helicoPos;

			// on prend la position de la balle dans la fenetre
			aircraftPos.x = aircraftNow->positionWin.x;
			aircraftPos.y = aircraftNow->positionWin.y ;

			// on prend la position de l'helico dans la fenetre
			helicoPos.x = helico->positionWin.x;
			helicoPos.y = helico->positionWin.y + HELICO_CENTER_Y;

			// position initial de la balle	

			firePositionWin.x = (aircraftNow->directionX == direction_right) ? (aircraftNow->positionWin.x + aircraftNow->positionImage.w) : aircraftNow->positionWin.x;
			firePositionWin.y = aircraftNow->positionWin.y + aircraftNow->positionImage.h / 2 + 5;

			firePositionImage.x = FIRE_LEFT_AIRCRAFT_POSITION_X;
			firePositionImage.y = FIRE_AIRCRAFT_POSITION_Y;
			firePositionImage.w = FIRE_AIRCRAFT_WIDTH;
			firePositionImage.h = FIRE_AIRCRAFT_HEIGHT;

			// focus vers l'elico
			vector.x = (aircraftNow->directionX == direction_left) ?  -1 : 1;
			vector.y = 0;
				
			soundFireTank();
			addElementLast(listFireAircraft, &firePositionWin, &firePositionImage, normalize(&vector)); // ajout de la balle + son vecteur dans la liste
		}

		aircraftNow = aircraftNow->suivant;
	}
	
	Fire *fireNow = listFireAircraft->premier;
	
	while (fireNow != NULL ) // pour chaque balle des avions
	{
		newPosition->x = fireNow->positionWin.x + (fireNow->vector.x * refreshRate * FIRE_SPEED_AIRCRAFT); // mise à jour horizontal de la position de la balle

		if((newPosition->y >= POSITION_BOTTOM && fireNow->vector.y > 0) || newPosition->x <= 0 || newPosition->x + FIRE_AIRCRAFT_WIDTH > SCREEN_WIDTH)	// si y'a eu une collision
		{
			destroyElementPosition(listFireAircraft, fireNow->positionList); // on l'efface du tableau
		}
		else
		{
			fireNow->positionWin.x = newPosition->x;
			animFireAircraft(fireNow);
			targetFireAircraft(&fireNow->positionWin);
		}

		fireNow = fireNow->suivant;
	}
}

void updateExplosion(float refreshRate, SDL_Rect *newPosition)
{
	Explosion *explosionNow = listExplosion->premier;

	while (explosionNow != NULL) 
	{
		if (explosionNow->positionImage.w == EXPLOSION_PRISON_WIDTH)
		{
			animExplosionPrison(explosionNow);
		}
		else
		{
			if(explosionNow->positionWin.y < POSITION_BOTTOM)
				explosionNow->positionWin.y += (int) (refreshRate * VITESS_EXPLOSION);

			animExplosion(explosionNow);
		}
		
		explosionNow = explosionNow->suivant;
	}
}

void updateSaucer(float refreshRate, SDL_Rect *newPosition)
{
	Saucer *saucerNow = listSaucer->premier;

	while (saucerNow != NULL) 
	{
		Vector vector; 
		vector.x=0; vector.y=0;

		if(helico->positionWin.x + HELICO_CENTER_X < saucerNow->positionWin.x)
		{
			vector.x--;
		}
		else if(helico->positionWin.x + HELICO_CENTER_X > saucerNow->positionWin.x)
		{
			vector.x++;
		}

		if(helico->positionWin.y + HELICO_HEIGHT < saucerNow->positionWin.y)
		{
			vector.y--;
		}
		else if(helico->positionWin.y + HELICO_CENTER_Y > saucerNow->positionWin.y)
		{
			vector.y++;
		}

		normalize(&vector);

		newPosition->x = saucerNow->positionWin.x + (vector.x * refreshRate * VITESS_SAUCER);
		newPosition->y = saucerNow->positionWin.y + (vector.y * refreshRate * VITESS_SAUCER);

		if(collisionSaucer(saucerNow) == FALSE)
		{
			saucerNow->positionWin.x = newPosition->x;
			saucerNow->positionWin.y = newPosition->y;
			animSaucer(saucerNow);
		}

		saucerNow = saucerNow->suivant;
	}
}