#include "game.h"


void game()
{
	bool continuer = TRUE;

	menu = IMG_Load("sprites/menu.png");

	if(menu == NULL)
	{
		fprintf(stderr, "Erreur : Impossible de charger le menu  : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	FMOD_Sound_SetLoopCount(sound_menu, -1);

	FMOD_System_PlaySound(sound_system, 0, sound_menu, 0, &canal_bg); // lancement du son menu

	SDL_Rect positionMenu; 

	positionMenu.x = 0; positionMenu.y = 0;

	SDL_Event events;

	while (continuer)
    {
        SDL_WaitEvent(&events);

        switch(events.type)
        {
            case SDL_QUIT:
                continuer = FALSE;
                break;
            case SDL_KEYDOWN:
                switch (events.key.keysym.sym) {
                    case HARDK:  // Si on appuis sur Escpace on commence le jeux
                        mode = HARD;
						play();		
                        break;

                     case MEDIUMK:  // Si on appuis sur Escpace on commence le jeux
                        mode = MEDIUM;
						play();		
                        break;

                     case EASYK:  // Si on appuis sur Escpace on commence le jeux
                        mode = EASY;
						play();		
                        break;

                    case SDLK_ESCAPE: // Si on appuis sur Echap on quitte
                        continuer = FALSE;
                        break;

                    default :
                        break;
                }
                break;
        }

 		SDL_BlitSurface(menu, NULL, screen, &positionMenu); // On place le menu sur l'ecran principal
        SDL_Flip(screen); // Actualisation
    }

    SDL_FreeSurface(menu);
}

void play()
{
	Input keyPad;   // creation de notre structure keyPad

    memset(&keyPad, FALSE, sizeof(keyPad)); // on met tous ses variables à FALSE

    initStage();

	while (keyPad.quit == FALSE && keyPad.key[SDLK_ESCAPE] == FALSE && gameOver == FALSE) // boucle
    {
    	event(&keyPad);	// evenement (clavier)

        update(&keyPad);   // le coeur du jeu...
        
        blitAll(); // on blit le tout sur l'ecran
        
        SDL_Flip(screen); // mise à jour de l'ecran
        
        SDL_Delay(15);
    }

    deleteStage();
}

void event(Input *keyPad)
{
	SDL_Event events;

	SDL_PollEvent(&events);

	switch (events.type) {
		case SDL_KEYDOWN:
			keyPad->key[events.key.keysym.sym] = TRUE;
			break;
		
		case SDL_KEYUP:
			keyPad->key[events.key.keysym.sym] = FALSE;
			break;

		case SDL_QUIT:
			keyPad->quit = TRUE;
			break;
	}
}

void update(Input *keyPad)
{
	float refreshRate = myRefresh();
	
	SDL_Rect newPosition;

	updateHelico(keyPad, refreshRate, &newPosition);
	updateBackground(keyPad, refreshRate, &newPosition);
	updateBalleHelico(keyPad, refreshRate, &newPosition);
	updateTank(refreshRate, &newPosition);
	updateOtage(refreshRate, &newPosition);
	updateAircraft(refreshRate, &newPosition);
	updateSaucer(refreshRate, &newPosition);
	updateExplosion(refreshRate, &newPosition);
	updateText();
	world();

	theEnd();
}

void updateHelico(Input *keyPad, float refreshRate, SDL_Rect *newPosition)
{
	if(helico->isDeath == TRUE)
		return;

	newPosition->x = helico->positionWin.x;
	newPosition->y = helico->positionWin.y;

	if(keyPad->key[UP])
	{
		newPosition->y -= (int) (refreshRate * VITESS_HELICO);
	}

	if(helico->positionWin.y + HELICO_HEIGHT < POSITION_BOTTOM-2)
	{
		if(keyPad->key[LEFT]  && !keyPad->key[SCROLL_LEFT] && !keyPad->key[RIGHT])
		{
			newPosition->x -= (int) (refreshRate * VITESS_HELICO);
		}

		if(keyPad->key[RIGHT] && !keyPad->key[SCROLL_RIGHT] && !keyPad->key[LEFT])
		{
			newPosition->x += (int) (refreshRate * VITESS_HELICO);
		}
	}

	if(keyPad->key[DOWN])
	{
		newPosition->y += (int) (refreshRate * VITESS_HELICO);
	}

	if(keyPad->key[TURN]) // si on appuis sur A
	{
		keyPad->key[TURN] = FALSE; // on desactive la touche 

		if(helico->direction == D_LEFT)
		{
			helico->direction = D_FORWARD;
			helico->oldDirection = D_LEFT;
			helico->positionImage.x = HELICO_POSITION_FORWARD_X;
		}
		else if(helico->direction == D_RIGHT)
		{
			helico->direction = D_FORWARD;
			helico->oldDirection = D_RIGHT;
			helico->positionImage.x = HELICO_POSITION_FORWARD_X;
		}
		else
			helico->direction = (helico->oldDirection == D_LEFT) ? D_RIGHT : D_LEFT;
	}

	if((newPosition->x) > 0 && (newPosition->x + helico->positionImage.w) <= SCREEN_WIDTH &&
		(newPosition->y) > 0 && (newPosition->y + helico->positionImage.h) <= POSITION_BOTTOM)
	{
		helico->positionWin.x = newPosition->x;
		helico->positionWin.y = newPosition->y;
	}

	animHelico(keyPad);
	soundHelico();
	gravity(keyPad, refreshRate);
}

void updateBackground(Input *keyPad, float refreshRate, SDL_Rect *newPosition)
{
	if(helico->isDeath == TRUE)
		return;

	if (helico->positionWin.y + HELICO_HEIGHT > POSITION_BOTTOM-2) // si l'elico se pose, on ne fait pas bougé le background
		return;

	newPosition->x = backgroundPositionImage.x;
	newPosition->y = backgroundPositionImage.y;  

	if(keyPad->key[RIGHT] && helico->positionWin.x >= RIGHT_WALL && newPosition->x < BACKGROUND_WIDTH - SCREEN_WIDTH)
	{
		keyPad->key[SCROLL_RIGHT] = TRUE;
		newPosition->x += (int) (refreshRate * VITESS_BACKGROUND);
	}

	if(helico->positionWin.x < RIGHT_WALL || newPosition->x >= BACKGROUND_WIDTH - SCREEN_WIDTH)
	{
		keyPad->key[SCROLL_RIGHT] = FALSE;
	}

	if(keyPad->key[LEFT] && helico->positionWin.x <= LEFT_WALL && newPosition->x > 0 )
	{
		keyPad->key[SCROLL_LEFT] = TRUE;
		newPosition->x -= (int) (refreshRate * VITESS_BACKGROUND);
	}

	if(helico->positionWin.x > LEFT_WALL || newPosition->x <= 0)
	{
		keyPad->key[SCROLL_LEFT] = FALSE;
	}

	if(newPosition->x >= 0 && newPosition->x <= BACKGROUND_WIDTH - SCREEN_WIDTH)
	{
		if(newPosition->x != backgroundPositionImage.x)
			updatePositionOnBackground(refreshRate, backgroundPositionImage.x, newPosition->x);

		backgroundPositionImage.x = newPosition->x;
	}
}

void updatePositionOnBackground(float refreshRate, float oldPosition, float newPosition)
{
	if(oldPosition > newPosition)
	{
		Tank *tankNow = listTank->premier;

		while(tankNow != NULL)
		{
			tankNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);

			tankNow = tankNow->suivant;
		}
		
		Fire *fireNow = listFireTank->premier;

		while (fireNow != NULL) {
			fireNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			fireNow = fireNow->suivant;
		}

		Fire *fireAircraftNow = listFireAircraft->premier;

		while (fireAircraftNow != NULL) {
			fireAircraftNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			fireAircraftNow = fireAircraftNow->suivant;
		}

		Otage *otageNow = listOtage->premier;

		while (otageNow != NULL) {
			otageNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			otageNow = otageNow->suivant;
		}

		Aircraft *aircraftNow = listAircraft->premier;

		while (aircraftNow != NULL) {
			aircraftNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			aircraftNow = aircraftNow->suivant;
		}

		Saucer *saucerNow = listSaucer->premier;

		while (saucerNow != NULL) {
			saucerNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			saucerNow = saucerNow->suivant;
		}

		Explosion *explosionNow = listExplosion->premier;

		while (explosionNow != NULL) {
			explosionNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			explosionNow = explosionNow->suivant;
		}

		Prison *prisonNow = listPrison->premier;

		while (prisonNow != NULL) {
			prisonNow->positionWin.x += (int) (refreshRate * VITESS_BACKGROUND);
			prisonNow = prisonNow->suivant;
		}
	}
	else
	{
		Tank *tankNow = listTank->premier;

		while(tankNow != NULL)
		{
			tankNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);

			tankNow = tankNow->suivant;
		}

		Fire *fireNow = listFireTank->premier;

		while (fireNow != NULL) {
			fireNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			fireNow = fireNow->suivant;
		}

		Fire *fireAircraftNow = listFireAircraft->premier;

		while (fireAircraftNow != NULL) {
			fireAircraftNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			fireAircraftNow = fireAircraftNow->suivant;
		}

		Otage *otageNow = listOtage->premier;
		
		while (otageNow != NULL) {
			otageNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			otageNow = otageNow->suivant;
		}

		Aircraft *aircraftNow = listAircraft->premier;

		while (aircraftNow != NULL) {
			aircraftNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			aircraftNow = aircraftNow->suivant;
		}

		Saucer *saucerNow = listSaucer->premier;

		while (saucerNow != NULL) {
			saucerNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			saucerNow = saucerNow->suivant;
		}

		Explosion *explosionNow = listExplosion->premier;

		while (explosionNow != NULL) {
			explosionNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			explosionNow = explosionNow->suivant;
		}

		Prison *prisonNow = listPrison->premier;

		while (prisonNow != NULL) {
			prisonNow->positionWin.x -= (int) (refreshRate * VITESS_BACKGROUND);
			prisonNow = prisonNow->suivant;
		}
	}
}

void updateBalleHelico(Input *keyPad, float refreshRate, SDL_Rect *newPosition)
{

	if(keyPad->key[SDLK_SPACE] && timeAllowed(&helico->previousTimeFire, TIME_FIRE_HELICO) && helico->isDeath == FALSE)
	{
		SDL_Rect firePositionWin;
		SDL_Rect firePositionImage;
		Vector   vector;

		vector.x = 0;
		vector.y = 0;

		firePositionWin.x = helico->positionWin.x + helico->positionFire;
		firePositionWin.y = helico->positionWin.y + HELICO_HEIGHT - 18;

		firePositionImage.x = FIRE_POSITION_X;
		firePositionImage.y = FIRE_POSITION_Y;
		firePositionImage.w = FIRE_WIDTH;
		firePositionImage.h = FIRE_HEIGHT;

		if(helico->direction == D_RIGHT && keyPad->key[RIGHT] == FALSE && keyPad->key[LEFT] == FALSE)
		{
			vector.x++;
		}
		else if(helico->direction == D_RIGHT && (keyPad->key[RIGHT] == TRUE || keyPad->key[LEFT] == TRUE))
		{
			vector.x++;
			vector.y++;
		}
		else if(helico->direction == D_LEFT && keyPad->key[RIGHT] == FALSE && keyPad->key[LEFT] == FALSE)
		{
			vector.x--;
		}
		else if(helico->direction == D_LEFT && (keyPad->key[LEFT] == TRUE || keyPad->key[RIGHT] == TRUE))
		{
			vector.x--;
			vector.y++;
		}
		else if(helico->direction == D_FORWARD && keyPad->key[RIGHT] == FALSE && keyPad->key[LEFT] == FALSE)
		{
			vector.y++;
		}
		else if(helico->direction == D_FORWARD && keyPad->key[RIGHT] == TRUE && keyPad->key[LEFT] == FALSE)
		{
			vector.x -= 0.2;
			vector.y++;
		}
		else if(helico->direction == D_FORWARD && keyPad->key[RIGHT] == FALSE && keyPad->key[LEFT] == TRUE)
		{
			vector.x += 0.2;
			vector.y++;
		}

		soundFire();

		addElementLast(listFireHelico, &firePositionWin, &firePositionImage, normalize(&vector));
	}

	Fire *fireNow = listFireHelico->premier;

	while (fireNow != NULL)
	{
		newPosition->x = fireNow->positionWin.x + (fireNow->vector.x * refreshRate * FIRE_SPEED);
		newPosition->y = fireNow->positionWin.y + (fireNow->vector.y * refreshRate * FIRE_SPEED);

		if((newPosition->x)  > 0 && (newPosition->x + FIRE_WIDTH) <= SCREEN_WIDTH &&
			(newPosition->y) > 0 && (newPosition->y + FIRE_HEIGHT) <= POSITION_TANK_DEFAULT)
		{
			fireNow->positionWin.x = newPosition->x;
			fireNow->positionWin.y = newPosition->y;

			animFire(fireNow);

			targetFireHelico(fireNow);
		}
		else
		{
			destroyElementPosition(listFireHelico, fireNow->positionList);
		}

		fireNow = fireNow->suivant;
	}
}

void theEnd() // conditions de victoires
{
	if((listOtage->nbr_element + helico->otage + helico->otageSuccoured < 16 && listPrison->nbr_element == 1) || (listOtage->nbr_element + helico->otage + helico->otageSuccoured < 32 && listPrison->nbr_element == 0))
	{
		helico->hp = 1;
		helico->isDeath = TRUE;
	}

	if(helico->otageSuccoured >= NB_OTAGE_MINI_WIN && helico->otage == 0 && listPrison->nbr_element == 0 && listOtage->nbr_element == 0 && ((helico->isDeath == TRUE && helico->hp >= 1) || helico->isDeath == FALSE))
	{
		helico->win = TRUE;
	}

	if (helico->isDeath == TRUE)
	{
		SDL_Rect position;
		position.x = 0; position.y = 0;

		position.x = helico->positionWin.x;
		position.y = helico->positionWin.y;

		if(explosionHelicoCreated == FALSE && helico->win == FALSE)
		{	
			soundExplosion();
			createExplosion(&position);
			timeForSpawnHelico = SDL_GetTicks();
			explosionHelicoCreated = TRUE;
		}

		if(timeAllowed(&timeForSpawnHelico, TIME_DISABLE_MESSAGE))
		{
			if(helico->hp == 1)
				gameOver = TRUE;
			else
				replay();
		}
	}

	if(helico->win == TRUE)
	{
		if(initializeTimeMessage ==  FALSE)
		{
			timeWinMessage = SDL_GetTicks();
			initializeTimeMessage = TRUE;
		}

		if(timeAllowed(&timeWinMessage, TIME_DISABLE_MESSAGE))
		{
			gameOver = TRUE;
		}
	}
}

void world()
{
	if(mode == HARD)
	{
		Prison *prisonNow = listPrison->premier;

		while (prisonNow != NULL) 
		{
			if(helico->positionWin.x - prisonNow->positionWin.x > DISTANCE_PRISON_SPAWN_TANK_RIGHT ^ prisonNow->positionWin.x - helico->positionWin.x < DISTANCE_PRISON_SPAWN_TANK_LEFT && timeAllowed(&prisonNow->previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_HARD)
			{
				addTankLast(listTank, prisonNow->positionWin.x);
			}

			prisonNow = prisonNow->suivant;
		}

		if (helico->positionWin.y + HELICO_HEIGHT >= POSITION_BOTTOM-3 && helico->positionWin.x > (POSITION_MIN_SPAWN_TANK - backgroundPositionImage.x) && timeAllowed(&previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_HARD)
		{
			addTankLast(listTank, helico->positionWin.x + DISTANCE_SPAWN_TANK);
		}

		if((helico->otage > NBR_OTAGE_TO_SPAWN_AIRCRAFT || helico->otageSuccoured > NBR_OTAGE_TO_SPAWN_AIRCRAFT) && timeAllowed(&previousTimeSpawnAircraft, TIME_SPAWN_AIRCRAFT) && listAircraft->nbr_element < NB_AIRCRAFT_MAX_HARD)
		{
			SDL_Rect aircracftPositionWin;
			DirectionX directionX = direction_left;

			aircracftPositionWin.x = helico->positionWin.x + DISTANCE_SPAWN_AIRCRAFT;
			aircracftPositionWin.y = helico->positionWin.y;

			addAircraftLast(listAircraft, &aircracftPositionWin, &directionX);
		}

		if(helico->otageSuccoured > NB_OTAGE_FOR_SPAWN_SAUCER && timeAllowed(&previousTimespawnSaucer, TIME_SPAWN_SAUCER_HARD) && listSaucer->nbr_element < NB_SAUCER_MAX)
		{
			SDL_Rect position;

			position.x = helico->positionWin.x + DISTANCE_SPAWN_SAUCER;
			position.y = helico->positionWin.y;
			DirectionX direction = direction_left;

			addSaucerLast(listSaucer, &position, &direction);
		}
	}
	else if(mode == MEDIUM)
	{
		Prison *prisonNow = listPrison->premier;

		while (prisonNow != NULL) 
		{
			if(helico->positionWin.x - prisonNow->positionWin.x > DISTANCE_PRISON_SPAWN_TANK_RIGHT ^ prisonNow->positionWin.x - helico->positionWin.x < DISTANCE_PRISON_SPAWN_TANK_LEFT && timeAllowed(&prisonNow->previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_MEDIUM)
			{
				addTankLast(listTank, prisonNow->positionWin.x);
			}

			prisonNow = prisonNow->suivant;
		}

		if (helico->positionWin.y + HELICO_HEIGHT >= POSITION_BOTTOM-3 && helico->positionWin.x > (POSITION_MIN_SPAWN_TANK - backgroundPositionImage.x) && timeAllowed(&previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_MEDIUM)
		{
			addTankLast(listTank, helico->positionWin.x + DISTANCE_SPAWN_TANK);
		}

		if(helico->otage > NBR_OTAGE_TO_SPAWN_AIRCRAFT && timeAllowed(&previousTimeSpawnAircraft, TIME_SPAWN_AIRCRAFT) && listAircraft->nbr_element < NB_AIRCRAFT_MAX_MEDIUM)
		{
			SDL_Rect aircracftPositionWin;
			DirectionX directionX = direction_left;

			aircracftPositionWin.x = helico->positionWin.x + DISTANCE_SPAWN_AIRCRAFT;
			aircracftPositionWin.y = helico->positionWin.y;

			addAircraftLast(listAircraft, &aircracftPositionWin, &directionX);
		}

		if(helico->otageSuccoured > NB_OTAGE_FOR_SPAWN_SAUCER && timeAllowed(&previousTimespawnSaucer, TIME_SPAWN_SAUCER_MEDIUM) && listSaucer->nbr_element < NB_SAUCER_MAX)
		{
			SDL_Rect position;

			position.x = helico->positionWin.x + DISTANCE_SPAWN_SAUCER;
			position.y = helico->positionWin.y;
			DirectionX direction = direction_left;

			addSaucerLast(listSaucer, &position, &direction);
		}
	}
	else
	{
		Prison *prisonNow = listPrison->premier;

		while (prisonNow != NULL) 
		{
			if(helico->positionWin.x - prisonNow->positionWin.x > DISTANCE_PRISON_SPAWN_TANK_RIGHT ^ prisonNow->positionWin.x - helico->positionWin.x < DISTANCE_PRISON_SPAWN_TANK_LEFT && timeAllowed(&prisonNow->previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_EASY)
			{
				addTankLast(listTank, prisonNow->positionWin.x);
			}

			prisonNow = prisonNow->suivant;
		}

		if (helico->positionWin.y + HELICO_HEIGHT >= POSITION_BOTTOM-3 && helico->positionWin.x > (POSITION_MIN_SPAWN_TANK - backgroundPositionImage.x) && timeAllowed(&previousTimeSpawnTank, TIME_SPAWN_TANK) && listTank->nbr_element < NB_TANK_MAX_EASY)
		{
			addTankLast(listTank, helico->positionWin.x + DISTANCE_SPAWN_TANK);
		}

		if(helico->otage > NBR_OTAGE_TO_SPAWN_AIRCRAFT && timeAllowed(&previousTimeSpawnAircraft, TIME_SPAWN_AIRCRAFT) && listAircraft->nbr_element < NB_AIRCRAFT_MAX_EASY)
		{
			SDL_Rect aircracftPositionWin;
			DirectionX directionX = direction_left;

			aircracftPositionWin.x = helico->positionWin.x + DISTANCE_SPAWN_AIRCRAFT;
			aircracftPositionWin.y = helico->positionWin.y;

			addAircraftLast(listAircraft, &aircracftPositionWin, &directionX);
		}

		if(helico->otageSuccoured > NB_OTAGE_FOR_SPAWN_SAUCER && timeAllowed(&previousTimespawnSaucer, TIME_SPAWN_SAUCER_EASY) && listSaucer->nbr_element < NB_SAUCER_MAX)
		{
			SDL_Rect position;

			position.x = helico->positionWin.x + DISTANCE_SPAWN_SAUCER;
			position.y = helico->positionWin.y;
			DirectionX direction = direction_left;

			addSaucerLast(listSaucer, &position, &direction);
		}
	}
}