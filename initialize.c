#include "initialize.h"


void initWindow()
{
	SDL_Init(SDL_INIT_VIDEO); // initialisation en mode video

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // allocation de la memoir pour la fenetre

	if(screen == NULL) // gestion d'erreur
	{
		fprintf(stderr, "Erreur : Impossible de charger le mode video  : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Choplifter", NULL);
}

void initSounds()
{
	FMOD_System_Create(&sound_system);
    FMOD_System_Init(sound_system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(sound_system, "sounds/background.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &sound_bg);
    FMOD_System_CreateSound(sound_system, "sounds/menu.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &sound_menu);
    FMOD_System_CreateSound(sound_system, "sounds/heli.wav", FMOD_CREATESAMPLE, 0, &sound_helico);
    FMOD_System_CreateSound(sound_system, "sounds/GE_Silencer.wav", FMOD_CREATESAMPLE, 0, &sound_fire);
    FMOD_System_CreateSound(sound_system, "sounds/fire.mp3", FMOD_CREATESAMPLE, 0, &sound_fire_tank);
    FMOD_System_CreateSound(sound_system, "sounds/explosion.wav", FMOD_CREATESAMPLE, 0, &sound_explosion);
}

void initTexts()
{
	if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("font/ARBERKLEY.ttf", 25);
    policeGameOver = TTF_OpenFont("font/ARBERKLEY.ttf", 50);
    textOtage.position.x = POSITION_TEXT_OTAGE;

    textOtageSuccoured.position.x = POSITION_TEXT_OTAGE_SUCCOURED;

    textHelicoHp.position.x = POSITION_TEXT_HELICO_HP;

    textGameOver.position.x = POSITION_TEXT_GAME_OVER_X;
    textGameOver.position.y = POSITION_TEXT_GAME_OVER_Y;

    textWin.position.x = POSITION_TEXT_GAME_OVER_X;
    textWin.position.y = POSITION_TEXT_GAME_OVER_Y;
}

void initStage()
{
	gameOver = FALSE;

	listFireHelico   = initialisation();
	listFireTank     = initialisation();
	listFireAircraft = initialisation();
	listOtage        = initialisationOtage();
	listAircraft     = initialisationAircraft();
	listTank         = initialisationTank();
	listExplosion    = initialisationExplosion();
	listPrison       = initialisationPrison();
	listSaucer       = initialisationSaucer();

	background = IMG_Load("sprites/background.bmp");
	sprite     = IMG_Load("sprites/sprites.gif");
	helico     = malloc(sizeof(Helico));

	if( background == NULL || sprite == NULL || helico == NULL) // gestion d'erreur (pointeur)
	{
		fprintf(stderr, "Erreur : Mémoire insuffisante : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// definition de la position initiale de l'image de fond par rapport à l'image
	backgroundPositionImage.x  = 0;
	backgroundPositionImage.y  = 0;
	backgroundPositionImage.w  = SCREEN_WIDTH;
	backgroundPositionImage.h  = SCREEN_HEIGHT;

	// definition de la position initiale de l'image de fond par rapport à la fenêtre
	backgroundPositionWin.x  = 0;
	backgroundPositionWin.y  = 0;

	// definition de la position initiale de l'helico par rapport à l'image
	helico->positionImage.x  = HELICO_POSITION_RIGHT_X;
	helico->positionImage.y  = HELICO_POSITION_Y;
	helico->positionImage.w  = HELICO_WIDTH;
	helico->positionImage.h  = HELICO_HEIGHT;

	helico->previousTimeAnimation = SDL_GetTicks();
	helico->direction = D_LEFT;
	helico->previousTimeFire = FIRE_LEFT;
	helico->otage = 0;
	helico->otageSuccoured = 0;
	helico->hp = HP_HELICO_DEFAULT;
	helico->isDeath = FALSE;
	helico->win = FALSE;

	explosionHelicoCreated = FALSE;
	initializeTimeMessage  = FALSE;

	// definition de la position initiale de l'helico par rapport à la fenêtre
	helico->positionWin.x  = POSITION_BASE - helico->positionImage.w/2;
	helico->positionWin.y  = POSITION_BOTTOM - helico->positionImage.h;

	createPrison();

	// sons
	FMOD_Channel_Stop(canal_bg);

	FMOD_Sound_SetLoopCount(sound_bg, -1);

	FMOD_System_PlaySound(sound_system, 30, sound_bg, 0, &canal_bg);
}

void deleteStage()
{
	// lists

	listFireTank     = destroyElementList(listFireTank);
	listFireAircraft = destroyElementList(listFireAircraft);
	listFireHelico   = destroyElementList(listFireHelico);
	listExplosion    = destroyExplosionList(listExplosion);
	listAircraft     = destroyAircraftList(listAircraft);
	listTank         = destroyTankList(listTank);
	listOtage        = destroyOtageList(listOtage);
	listPrison       = destroyPrisonList(listPrison);

	// helico

	free(helico);
	helico = NULL;

	// sprites

	SDL_FreeSurface(background);
	SDL_FreeSurface(sprite);

	// sons
	FMOD_Channel_Stop(canal_bg);
	FMOD_Channel_Stop(canal_game);

	FMOD_Sound_SetLoopCount(sound_menu, -1);

	FMOD_System_PlaySound(sound_system, 0, sound_menu, 0, &canal_bg);
}

void initAll()
{
	initWindow();   // initialisation de la fenêtre
    initSounds();   // initialisation des sons
    initTexts();	// initialisation du texte
    initTimers();	// initialisation du temps
}

void createPrison()
{
	int i, pos = 0;

	SDL_Rect prisonPositionWin;
	SDL_Rect prisonPositionImage;

	for (i = 0; i < NB_PRISON; ++i)
	{
		pos += BACKGROUND_WIDTH/4;

		prisonPositionImage.x = PRISON_POSITION_X;
		prisonPositionImage.y = PRISON_POSITION_Y;
		prisonPositionImage.w = PRISON_WIDTH;
		prisonPositionImage.h = PRISON_HEIGHT;
     
		prisonPositionWin.x =  pos;
		prisonPositionWin.y = POSITION_BOTTOM - PRISON_HEIGHT;

		addPrisonLast(listPrison, &prisonPositionWin, &prisonPositionImage);
	}
}

void createOtage(int nbr_otage, SDL_Rect *otagePositionWin, DirectionX *direction) 
{
	int i;

	SDL_Rect otagePositionImage;

	for (i = 0; i < nbr_otage; ++i)
	{
		otagePositionImage.x = OTAGE_POSITION_X;

		if(*direction == direction_left)
			otagePositionImage.y = OTAGE_POSITION_LEFT_Y;
		else
			otagePositionImage.y = OTAGE_POSITION_RIGHT_Y;

		otagePositionImage.w = OTAGE_WIDTH;
		otagePositionImage.h = OTAGE_HEIGHT;

		otagePositionWin->x += OTAGE_WIDTH;

		addOtageLast(listOtage, otagePositionWin, &otagePositionImage, direction);
	}
}

void createExplosion(SDL_Rect *explosionPositionWin)
{
	SDL_Rect explosionPositionImage;
	
	// definition de la position initiale de l'explosion par rapport à l'image
	explosionPositionImage.x  = EXPLOSION_POSITION_X;
	explosionPositionImage.y  = EXPLOSION_POSITION_Y;
	explosionPositionImage.w  = EXPLOSION_WIDTH;
	explosionPositionImage.h  = EXPLOSION_HEIGHT;

	addExplosionLast(listExplosion, explosionPositionWin, &explosionPositionImage);
}

void createExplosionPrison(SDL_Rect *explosionPositionWin)
{
	SDL_Rect explosionPositionImage;
	
	// definition de la position initiale de l'explosion par rapport à l'image
	explosionPositionImage.x  = EXPLOSION_PRISON_POSITION_X;
	explosionPositionImage.y  = EXPLOSION_PRISON_POSITION_Y;
	explosionPositionImage.w  = EXPLOSION_PRISON_WIDTH;
	explosionPositionImage.h  = EXPLOSION_PRISON_HEIGHT;

	addExplosionLast(listExplosion, explosionPositionWin, &explosionPositionImage);
}

void blitAll()
{
	// background
	blit(background, &backgroundPositionImage, &backgroundPositionWin);

    // vehicle
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 132, 154, 181));

    // prison

    blit(textOtage.text, NULL, &textOtage.position);
    blit(textOtageSuccoured.text, NULL, &textOtageSuccoured.position);
    blit(textHelicoHp.text, NULL, &textHelicoHp.position);
    
    Prison *prisonNow = listPrison->premier;

	while (prisonNow != NULL) // on parcourt la liste des prisons 
	{
		blit(sprite, &prisonNow->positionImage, &prisonNow->positionWin);
		
		prisonNow = prisonNow->suivant;
	}

	if(helico->isDeath == FALSE)
   		blit(sprite, &helico->positionImage, &helico->positionWin);

    // fire
	Fire *fireNow = listFireHelico->premier;

	while (fireNow != NULL) // on parcourt la liste des balles de l'elico
	{
		blit(sprite, &fireNow->positionImage, &fireNow->positionWin);

		fireNow = fireNow->suivant;
	}

	fireNow = listFireTank->premier;

	while (fireNow != NULL) // on parcourt la liste des balles des tanks
	{
		blit(sprite, &fireNow->positionImage, &fireNow->positionWin);

		fireNow = fireNow->suivant;
	}

	fireNow = listFireAircraft->premier;

	while (fireNow != NULL) // on parcourt la liste des balles des avions
	{
		blit(sprite, &fireNow->positionImage, &fireNow->positionWin);

		fireNow = fireNow->suivant;
	}

	// tank
    
    Tank *tankNow = listTank->premier;

	while (tankNow != NULL) // on parcourt la liste des tanks 
	{
		blit(sprite, &tankNow->positionImage, &tankNow->positionWin);
		
		tankNow = tankNow->suivant;
	}
	
	Otage *otageNow = listOtage->premier;

	while (otageNow != NULL) // on parcourt la liste des otages 
	{
		blit(sprite, &otageNow->positionImage, &otageNow->positionWin);
		
		otageNow = otageNow->suivant;
	}

	Aircraft *aircraftNow = listAircraft->premier;

	while (aircraftNow != NULL) // on parcourt la liste des avions 
	{
		blit(sprite, &aircraftNow->positionImage, &aircraftNow->positionWin);
		
		aircraftNow = aircraftNow->suivant;
	}

	Saucer *saucerNow = listSaucer->premier;

	while (saucerNow != NULL) // on parcourt la liste des soucoupes 
	{
		blit(sprite, &saucerNow->positionImage, &saucerNow->positionWin);
		
		saucerNow = saucerNow->suivant;
	}

	Explosion *explosionNow = listExplosion->premier;

	while (explosionNow != NULL) // on parcourt la liste des explosions 
	{
		blit(sprite, &explosionNow->positionImage, &explosionNow->positionWin);
		
		explosionNow = explosionNow->suivant;
	}

	if(helico->isDeath == TRUE && helico->hp == 1)
		blit(textGameOver.text, NULL, &textGameOver.position);

	if(helico->win == TRUE)
		blit(textWin.text, NULL, &textWin.position);
}

void blit(SDL_Surface *src, SDL_Rect *posImg, SDL_Rect *posWin)	// creation d'une copie, car la valeur est parfois modifiée
{
	SDL_Rect copyPosition;

	copyPosition.x = posWin->x;
	copyPosition.y = posWin->y;

	SDL_BlitSurface(src, posImg, screen, &copyPosition);
}

void quit() // liberation de la memoir du son, text, et SDL
{
	deleteSound();
	deleteTexts();
	SDL_Quit();
}

void deleteSound()	
{
	FMOD_Sound_Release(sound_fire);
	FMOD_Sound_Release(sound_helico);
	FMOD_Sound_Release(sound_explosion);
	FMOD_Sound_Release(sound_fire_tank);
	FMOD_Sound_Release(sound_bg);
	FMOD_Sound_Release(sound_menu);
    FMOD_System_Close(sound_system);
    FMOD_System_Release(sound_system);
}

void deleteTexts()
{
	TTF_CloseFont(police);
	TTF_CloseFont(policeGameOver);
    TTF_Quit();

	SDL_FreeSurface(textOtage.text);
	SDL_FreeSurface(textOtageSuccoured.text);
	SDL_FreeSurface(textHelicoHp.text);
	SDL_FreeSurface(textGameOver.text);
	SDL_FreeSurface(textWin.text);
}

void replay()
{

	int oldbackgroundPositionImageX = backgroundPositionImage.x;

	// definition de la position initiale de l'image de fond par rapport à l'image
	backgroundPositionImage.x  = 0;
	backgroundPositionImage.y  = 0;

	helico->direction = D_LEFT;
	helico->positionFire = FIRE_LEFT;
	helico->otage = 0;
	helico->hp--;
	helico->isDeath = FALSE;
	helico->win = FALSE;

	explosionHelicoCreated = FALSE;

	// definition de la position initiale de l'helico par rapport à la fenêtre
	helico->positionWin.x  = POSITION_BASE - helico->positionImage.w/2;
	helico->positionWin.y  = POSITION_BOTTOM - helico->positionImage.h;

	Saucer *saucer = listSaucer->premier;

	while (saucer != NULL) {
		destroySaucerPosition(listSaucer, saucer->positionList);
		saucer = saucer->suivant;
	}

	Tank *tankNow = listTank->premier;

	while(tankNow != NULL)
	{
		tankNow->positionWin.x += oldbackgroundPositionImageX;

		tankNow = tankNow->suivant;
	}
	
	Fire *fireNow = listFireTank->premier;

	while (fireNow != NULL) {
		fireNow->positionWin.x += oldbackgroundPositionImageX;
		fireNow = fireNow->suivant;
	}

	Fire *fireAircraftNow = listFireAircraft->premier;

	while (fireAircraftNow != NULL) {
		fireAircraftNow->positionWin.x += oldbackgroundPositionImageX;
		fireAircraftNow = fireAircraftNow->suivant;
	}

	Otage *otageNow = listOtage->premier;

	while (otageNow != NULL) {
		otageNow->positionWin.x += oldbackgroundPositionImageX;
		otageNow = otageNow->suivant;
	}

	Aircraft *aircraftNow = listAircraft->premier;

	while (aircraftNow != NULL) {
		aircraftNow->positionWin.x += oldbackgroundPositionImageX;
		aircraftNow = aircraftNow->suivant;
	}

	Explosion *explosionNow = listExplosion->premier;

	while (explosionNow != NULL) {
		explosionNow->positionWin.x += oldbackgroundPositionImageX;
		explosionNow = explosionNow->suivant;
	}

	Prison *prisonNow = listPrison->premier;

	while (prisonNow != NULL) {
		prisonNow->positionWin.x += oldbackgroundPositionImageX;
		prisonNow = prisonNow->suivant;
	}
}