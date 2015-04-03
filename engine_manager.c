#include "engine_manager.h"


ListeFire* initialisation()
{
    ListeFire *liste = malloc(sizeof(ListeFire)); // creation de la liste

    if(liste == NULL) // si l'allocation m'a pas marcher, on quite
    {
        exit(EXIT_FAILURE);
    }

    // initialisation de la liste
    liste->nbr_element = 0; 
    liste->premier = NULL;

    return liste;
}

void addElementFirst(ListeFire *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, Vector *vector)
{
    if(liste == NULL || vector == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Fire *nouveau = malloc(sizeof(Fire)); // creation de la balle

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // initialisation des variables

    Fire *aux = nouveau;

    nouveau->positionWin = *positionWin;

    nouveau->positionImage = *positionImage;
    
    nouveau->vector = *vector; 
    
    nouveau->positionList = (liste->premier == NULL) ? 1 : liste->premier->positionList;

    nouveau->previousTimeAnimation = 0;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau; // ajout de l'element dans la liste qui lui est dedié

    while (aux->suivant != NULL) // mise à jour des positions des elements dans la liste
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastElement(liste)->positionList; // mise à jour du nombre d'elements dans la liste
}

void addElementLast(ListeFire *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, Vector *vector)
{
    if(liste == NULL || vector == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Fire *dernier = lastElement(liste);

    if(dernier == NULL)
    {
    	addElementFirst(liste, positionWin, positionImage, vector);
    }
    else
    {
        Fire *nouveau = malloc(sizeof(Fire));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

    	dernier->suivant = nouveau;

	    nouveau->positionWin = *positionWin;

        nouveau->positionImage = *positionImage;

	    nouveau->vector= *vector; 

	    nouveau->positionList = dernier->positionList + 1;

        nouveau->previousTimeAnimation = 0;

	    nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastElement(liste)->positionList;
}


Fire* lastElement(ListeFire *liste) // retourne le dernier element de la liste
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Fire *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Fire* returnElementPosition(ListeFire *liste, int positionList) // retourne l'element qui correspond à la position que la fonction prend en argument
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Fire *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyElementPosition(ListeFire *liste, int pos) // detruit l'element dont la position est : pos et met à jour la liste
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Fire *aux = liste->premier;
    Fire *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnElementPosition(liste, pos + 1);

    before = returnElementPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }
}

void *destroyElementList(ListeFire *liste)  // detruit tous les element dans la lise, et la liste elle même
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Fire *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

// otages 

ListeOtage* initialisationOtage()
{
    ListeOtage *liste = malloc(sizeof(ListeOtage));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}

void addOtageFirst(ListeOtage *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, DirectionX *direction)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *nouveau = malloc(sizeof(Otage));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *aux = nouveau;

    nouveau->positionWin = *positionWin;
    
    nouveau->positionImage = *positionImage;

    nouveau->direction = *direction;

    nouveau->previousTimeAnimation = 0;
    
    nouveau->positionList = 1;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastOtage(liste)->positionList;
}

void addOtageLast(ListeOtage *liste, SDL_Rect *positionWin, SDL_Rect *positionImage, DirectionX *direction)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *dernier = lastOtage(liste);

    if(dernier == NULL)
    {
        addOtageFirst(liste, positionWin, positionImage, direction);
    }
    else
    {
        Otage *nouveau = malloc(sizeof(Otage));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        nouveau->positionWin = *positionWin;

        nouveau->positionImage = *positionImage;

        nouveau->direction = *direction; 

        nouveau->previousTimeAnimation = 0;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastOtage(liste)->positionList;
}

Otage* lastOtage(ListeOtage *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Otage* returnOtagePosition(ListeOtage *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Otage *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyOtagePosition(ListeOtage *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *aux = liste->premier;
    Otage *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnOtagePosition(liste, pos + 1);

    before = returnOtagePosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}

void *destroyOtageList(ListeOtage *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Otage *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

//  Aircraft

ListeAircraft* initialisationAircraft()
{
    ListeAircraft *liste = malloc(sizeof(ListeAircraft));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}


void addAircraftFirst(ListeAircraft *liste, SDL_Rect *positionWin, DirectionX *directionX)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *nouveau = malloc(sizeof(Aircraft));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *aux = nouveau;

    nouveau->positionWin = *positionWin;
    
    SDL_Rect positionImage;

    positionImage.x = AIRCRAFT_POSITION_X;

    if(*directionX == direction_left)
    {
        positionImage.y = AIRCRAFT_POSITION_LEFT_Y;
    }
    else
    {
        positionImage.y = AIRCRAFT_POSITION_RIGHT_Y;
    }
    
    positionImage.w = AIRCRAFT_WIDTH;
    positionImage.h = AIRCRAFT_HEIGHT;

    nouveau->positionImage = positionImage;

    nouveau->directionX = *directionX;

    nouveau->directionY = direction_bot;

    nouveau->oldPositionY = positionWin->y;

    nouveau->previousTimeAnimation = 0;

    nouveau->previousTimeFire = 0;
    
    nouveau->positionList = 1 ;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastAircraft(liste)->positionList;
}

void addAircraftLast(ListeAircraft *liste, SDL_Rect *positionWin, DirectionX *directionX)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *dernier = lastAircraft(liste);

    if(dernier == NULL)
    {
        addAircraftFirst(liste, positionWin, directionX);
    }
    else
    {
        Aircraft *nouveau = malloc(sizeof(Aircraft));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        nouveau->positionWin = *positionWin;

        SDL_Rect positionImage;

        positionImage.x = AIRCRAFT_POSITION_X;

        if(*directionX == direction_left)
        {
            positionImage.y = AIRCRAFT_POSITION_LEFT_Y;
        }
        else
        {
            positionImage.y = AIRCRAFT_POSITION_RIGHT_Y;
        }
        
        positionImage.w = AIRCRAFT_WIDTH;
        positionImage.h = AIRCRAFT_HEIGHT;

        nouveau->positionImage = positionImage;

        nouveau->directionX = *directionX;

        nouveau->directionY = direction_bot;

        nouveau->oldPositionY = positionWin->y;

        nouveau->previousTimeAnimation = 0;

        nouveau->previousTimeFire = 0;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastAircraft(liste)->positionList;
}

Aircraft* lastAircraft(ListeAircraft *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Aircraft* returnAircraftPosition(ListeAircraft *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Aircraft *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyAircraftPosition(ListeAircraft *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *aux = liste->premier;
    Aircraft *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnAircraftPosition(liste, pos + 1);

    before = returnAircraftPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}


void *destroyAircraftList(ListeAircraft *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Aircraft *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

//  Tank

ListeTank* initialisationTank()
{
    ListeTank *liste = malloc(sizeof(ListeTank));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}


void addTankFirst(ListeTank *liste, int positionX)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *nouveau = malloc(sizeof(Tank));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *aux = nouveau;

    SDL_Rect positionImage;
    SDL_Rect positionWin;

    // definition de la position initiale du tank par rapport à l'image
    positionImage.x  = TANK_POSITION_X;
    positionImage.y  = TANK_POSITION_Y;
    positionImage.w  = TANK_WIDTH;
    positionImage.h  = TANK_HEIGHT;

    positionWin.x = positionX;
    positionWin.y = POSITION_TANK_DEFAULT - TANK_HEIGHT;

    nouveau->positionWin = positionWin;

    nouveau->positionImage = positionImage;

    nouveau->previousTimeAnimation = 0;

    nouveau->previousTimeFire = 0;
    
    nouveau->positionCanon = 55;

    nouveau->positionList = 1 ;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastTank(liste)->positionList;
}

void addTankLast(ListeTank *liste, int positionX)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *dernier = lastTank(liste);

    if(dernier == NULL)
    {
        addTankFirst(liste, positionX);
    }
    else
    {
        Tank *nouveau = malloc(sizeof(Tank));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        SDL_Rect positionImage;
        SDL_Rect positionWin;

        // definition de la position initiale du tank par rapport à l'image
        positionImage.x  = TANK_POSITION_X;
        positionImage.y  = TANK_POSITION_Y;
        positionImage.w  = TANK_WIDTH;
        positionImage.h  = TANK_HEIGHT;

        positionWin.x = positionX;
        positionWin.y = POSITION_TANK_DEFAULT - TANK_HEIGHT;

        nouveau->positionWin = positionWin;

        nouveau->positionImage = positionImage;

        nouveau->previousTimeAnimation = 0;

        nouveau->previousTimeFire = 0;

        nouveau->positionCanon = 55;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastTank(liste)->positionList;
}

Tank* lastTank(ListeTank *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Tank* returnTankPosition(ListeTank *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Tank *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyTankPosition(ListeTank *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *aux = liste->premier;
    Tank *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnTankPosition(liste, pos + 1);

    before = returnTankPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}

void *destroyTankList(ListeTank *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Tank *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

//  Explosion

ListeExplosion* initialisationExplosion()
{
    ListeExplosion *liste = malloc(sizeof(ListeExplosion));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}


void addExplosionFirst(ListeExplosion *liste, SDL_Rect *positionWin, SDL_Rect *positionImage)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *nouveau = malloc(sizeof(Explosion));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *aux = nouveau;

    nouveau->positionWin = *positionWin;
    
    nouveau->positionImage = *positionImage;

    nouveau->previousTimeAnimation = 0;

    nouveau->positionList = 1 ;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastExplosion(liste)->positionList;
}

void addExplosionLast(ListeExplosion *liste, SDL_Rect *positionWin, SDL_Rect *positionImage)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *dernier = lastExplosion(liste);

    if(dernier == NULL)
    {
        addExplosionFirst(liste, positionWin, positionImage);
    }
    else
    {
        Explosion *nouveau = malloc(sizeof(Explosion));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        nouveau->positionWin = *positionWin;

        nouveau->positionImage = *positionImage;

        nouveau->previousTimeAnimation = 0;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastExplosion(liste)->positionList;
}

Explosion* lastExplosion(ListeExplosion *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Explosion* returnExplosionPosition(ListeExplosion *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Explosion *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyExplosionPosition(ListeExplosion *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *aux = liste->premier;
    Explosion *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnExplosionPosition(liste, pos + 1);

    before = returnExplosionPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}

void *destroyExplosionList(ListeExplosion *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Explosion *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

//  Prison

ListePrison* initialisationPrison()
{
    ListePrison *liste = malloc(sizeof(ListePrison));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}


void addPrisonFirst(ListePrison *liste, SDL_Rect *positionWin, SDL_Rect *positionImage)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *nouveau = malloc(sizeof(Prison));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *aux = nouveau;

    nouveau->positionWin = *positionWin;
    
    nouveau->positionImage = *positionImage;

    nouveau->previousTimeSpawnTank = TIME_SPAWN_TANK;

    nouveau->positionList = 1 ;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastPrison(liste)->positionList;
}

void addPrisonLast(ListePrison *liste, SDL_Rect *positionWin, SDL_Rect *positionImage)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *dernier = lastPrison(liste);

    if(dernier == NULL)
    {
        addPrisonFirst(liste, positionWin, positionImage);
    }
    else
    {
        Prison *nouveau = malloc(sizeof(Prison));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        nouveau->positionWin = *positionWin;

        nouveau->positionImage = *positionImage;

        nouveau->previousTimeSpawnTank = TIME_SPAWN_TANK;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastPrison(liste)->positionList;
}

Prison* lastPrison(ListePrison *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Prison* returnPrisonPosition(ListePrison *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Prison *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroyPrisonPosition(ListePrison *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *aux = liste->premier;
    Prison *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnPrisonPosition(liste, pos + 1);

    before = returnPrisonPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}

void *destroyPrisonList(ListePrison *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Prison *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}

//  Tank

ListeSaucer* initialisationSaucer()
{
    ListeSaucer *liste = malloc(sizeof(ListeSaucer));

    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    liste->nbr_element = 0;
    liste->premier = NULL;

    return liste;
}

void addSaucerFirst(ListeSaucer *liste, SDL_Rect *positionWin, DirectionX *directionX)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *nouveau = malloc(sizeof(Aircraft));

    if(nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *aux = nouveau;

    nouveau->positionWin = *positionWin;
    
     SDL_Rect positionImage;

    positionImage.x = SAUCER_POSITION_X;
    positionImage.y = SAUCER_POSITION_Y; 
        
    positionImage.w = SAUCER_WIDTH;
    positionImage.h = SAUCER_HEIGHT;

    nouveau->positionImage = positionImage;

    nouveau->directionX = *directionX;

    nouveau->directionY = direction_bot;

    // nouveau->oldPositionY = positionWin->y;

    nouveau->previousTimeAnimation = 0;

    nouveau->positionList = 1 ;

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

    while (aux->suivant != NULL)
    {
        aux->suivant->positionList++;
        aux = aux->suivant;
    }

    liste->nbr_element = lastSaucer(liste)->positionList;
}

void addSaucerLast(ListeSaucer *liste, SDL_Rect *positionWin, DirectionX *directionX)
{
    if(liste == NULL || positionWin == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *dernier = lastSaucer(liste);

    if(dernier == NULL)
    {
        addSaucerFirst(liste, positionWin, directionX);
    }
    else
    {
        Saucer *nouveau = malloc(sizeof(Aircraft));

        if(nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        dernier->suivant = nouveau;

        nouveau->positionWin = *positionWin;

        SDL_Rect positionImage;

        positionImage.x = SAUCER_POSITION_X;
        positionImage.y = SAUCER_POSITION_Y; 
            
        positionImage.w = SAUCER_WIDTH;
        positionImage.h = SAUCER_HEIGHT;

        nouveau->positionImage = positionImage;

        nouveau->directionX = *directionX;

        nouveau->directionY = direction_bot;

        // nouveau->oldPositionY = positionWin->y;

        nouveau->previousTimeAnimation = 0;

        nouveau->positionList = dernier->positionList + 1;

        nouveau->suivant = NULL;
    }
    
    liste->nbr_element = lastSaucer(liste)->positionList;
}

Saucer* lastSaucer(ListeSaucer *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *aux = liste->premier;

    if(aux != NULL)
    {
        while(aux->suivant != NULL)
        {
            aux = aux->suivant;
        }
    }

    return aux;
}

Saucer* returnSaucerPosition(ListeSaucer *liste, int positionList)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if(positionList < 1)
        return NULL;

    Saucer *aux = liste->premier;

    while(aux != NULL)
    {
        if(aux->positionList == positionList)
            break;

        aux = aux->suivant;
    }

    return aux;
}

void destroySaucerPosition(ListeSaucer *liste, int pos)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *aux = liste->premier;
    Saucer *next = NULL, *before = NULL;

    while (aux != NULL) {
        
        if(aux->positionList == pos)
        {
            free(aux);
            aux = NULL;
            break;
        }

        aux = aux->suivant;
    }

    next = returnSaucerPosition(liste, pos + 1);

    before = returnSaucerPosition(liste, pos - 1);

    if(before != NULL)
        before->suivant = (next == NULL) ?  NULL : next; 
    else
        liste->premier = (next == NULL) ?  NULL : next;

    aux = next;

    while(aux != NULL)
    {
        aux->positionList--;
        aux = aux->suivant;
    }

    liste->nbr_element -= 1;
}

void *destroySaucerList(ListeSaucer *liste)
{
    if(liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Saucer *aux = liste->premier;

    while (aux != NULL) {
            
        free(aux);

        aux = aux->suivant;
    }

    free(liste);

    return NULL;
}