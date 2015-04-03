#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "SDL/SDL.h"
#include "fmod.h"
#include "const.h"
#include "SDL_ttf/SDL_ttf.h"

// enumeration
typedef enum Direction Direction; // direction de l'helico
enum Direction
{
    D_RIGHT = 1 , D_LEFT = -1, D_FORWARD = 0
};

typedef enum DirectionX DirectionX; // direction de l'helico
enum DirectionX
{
    direction_right = 1 , direction_left = 0
};

typedef enum DirectionY DirectionY; // direction de l'helico
enum DirectionY
{
    direction_top = 1 , direction_bot = 0
};

typedef enum PositionFireHelico PositionFireHelico; // position par ou la balle va sortir de l'elico à differentes positions
enum PositionFireHelico
{
    FIRE_RIGHT = 65 , FIRE_LEFT = 15, FIRE_FORWARD = 38
};

// inputs
typedef struct Input
{
    char key[SDLK_LAST + VIRTUAL_KEYS];
    char quit;
} Input;

typedef struct Vector Vector;   // vecteur
struct Vector
{
    float x;
    float y;
};

typedef struct Helico Helico; // Helico
struct Helico
{
    SDL_Rect positionWin;   // position dans la fenetre
    SDL_Rect positionImage; // position dans notre image (sprites)

    Direction direction;    
    Direction oldDirection; // anicenne direction de l'helico
    PositionFireHelico positionFire;
    Uint8 hp;   // point de vie de l'elico
    bool isDeath;
    bool win;

    Uint8 otage; // otage dans l'elico
    Uint8 otageSuccoured; // otage secouru
    Uint32 previousTimeAnimation; // temps d'animation de l'helico
    Uint32 previousTimegravity; // temps d'animation de la gravité
    Uint32 previousTimeFire; // temps de tire
};

typedef struct Tank Tank;  
struct Tank
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;

    Uint16 positionCanon;   // position du canon (comme positionFireHelico)
    Uint32 previousTimeAnimation;
    Uint32 previousTimeFire;    // gere l'intervale de chaque tire

    int positionList;
    Tank *suivant;
};

typedef struct Fire Fire; // balle de l'helico & du tank
struct Fire
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;
    Uint32 previousTimeAnimation;
    Vector vector;


    int positionList;
    Fire *suivant;
};

typedef struct Otage Otage; // Otage
struct Otage
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;
    Uint32 previousTimeAnimation;
    DirectionX direction;
    Uint32 positionPrison;

    int positionList;
    Otage *suivant;
};

typedef struct Aircraft Aircraft; // Aircraft
struct Aircraft
{
    SDL_Rect positionWin;   // position dans la fenetre
    SDL_Rect positionImage; // position dans notre image (sprites)

    Uint16 positionFire;
    Uint32 previousTimeAnimation; // temps d'animation de l'helico
    Uint32 previousTimeFire; // temps de tire
    int oldPositionY;

    DirectionX directionX;
    DirectionY directionY;

    int positionList;
    Aircraft *suivant;
};

typedef struct Explosion Explosion; // Explosion
struct Explosion
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;
    Uint32 previousTimeAnimation;

    int positionList;
    Explosion *suivant;
};

typedef struct Prison Prison; // prison
struct Prison
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;
    Uint32 previousTimeSpawnTank; // temps pour que la prison apel un tank

    int positionList;
    Prison *suivant;
};

typedef struct Saucer Saucer; // soucoupe volante
struct Saucer
{
    SDL_Rect positionWin;
    SDL_Rect positionImage;
    Uint32 previousTimeAnimation;
    
    // int oldPositionY;
    
    DirectionX directionX;
    DirectionY directionY;

    int positionList;
    Saucer *suivant;
};


typedef struct ListeFire ListeFire; // liste des balles
struct ListeFire
{
    int nbr_element;
    Fire *premier;
};

typedef struct ListeOtage ListeOtage; // liste des balles
struct ListeOtage
{
    int nbr_element;
    Otage *premier;
};

typedef struct ListeTank ListeTank; // liste des Tank
struct ListeTank
{
    int nbr_element;
    Tank *premier;
};

typedef struct ListeAircraft ListeAircraft; // liste des Aircraft
struct ListeAircraft
{
    int nbr_element;
    Aircraft *premier;
};

typedef struct ListeExplosion ListeExplosion; // liste des Explosion
struct ListeExplosion
{
    int nbr_element;
    Explosion *premier;
};

typedef struct ListePrison ListePrison; // liste des Prison
struct ListePrison
{
    int nbr_element;
    Prison *premier;
};

typedef struct ListeSaucer ListeSaucer; // liste des Prison
struct ListeSaucer
{
    int nbr_element;
    Saucer *premier;
};

// surfaces
SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *sprite;
SDL_Surface *menu;

// background
SDL_Rect backgroundPositionImage;
SDL_Rect backgroundPositionWin;

// helico
Helico *helico;

// timers
Uint32 previousTime; // pour le refreshrate
Uint32 previousTimeSpawnTank; // temps pour spawn un tank
Uint32 previousTimeSpawnAircraft; // temps pour spawn un avion
Uint32 previousTimespawnOtage;  // temps pour spawn les otages quand l'elico les pause :D
Uint32 previousTimespawnSaucer;  // temps pour spawn une soucoupe volante o_O
Uint32 timeForSpawnHelico;
Uint32 previousTimeTurnOtage;
Uint32 timeWinMessage;

bool explosionHelicoCreated;
bool timePassedOtageTurn;
bool initializeTimeMessage;

// lists o_O
ListeFire *listFireHelico; // liste de balles propres à l'helico
ListeFire *listFireTank;    // la meme pour les tank
ListeFire *listFireAircraft;
ListeTank *listTank;
ListeOtage *listOtage;
ListePrison *listPrison;
ListeSaucer *listSaucer;
ListeAircraft *listAircraft;
ListeExplosion *listExplosion;

// police

typedef struct TextOtage TextOtage; // texte concernant le nombre d'otages
struct TextOtage
{
    SDL_Surface *text;
    SDL_Rect position;
};

typedef struct TextOtagesuccoured TextOtagesuccoured; // texte concernant le nombre d'otages secouru
struct TextOtagesuccoured
{
    SDL_Surface *text;
    SDL_Rect position;
};

typedef struct TextHelicoHp TextHelicoHp; // texte concernant le nombre de vie restant
struct TextHelicoHp
{
    SDL_Surface *text;
    SDL_Rect position;
};

typedef struct TextGameOver TextGameOver; // texte concernant le nombre de vie restant
struct TextGameOver
{
    SDL_Surface *text;
    SDL_Rect position;
};

typedef struct TextWin TextWin; // texte concernant le nombre de vie restant
struct TextWin
{
    SDL_Surface *text;
    SDL_Rect position;
};

TTF_Font *police;
TTF_Font *policeGameOver;
SDL_Color color;
TextOtage textOtage;
TextOtagesuccoured textOtageSuccoured;
TextHelicoHp textHelicoHp;
TextGameOver textGameOver;
TextWin textWin;

// sound

FMOD_SYSTEM *sound_system;
FMOD_SOUND  *sound_bg;
FMOD_SOUND *sound_menu;
FMOD_SOUND *sound_fire;
FMOD_SOUND *sound_helico;
FMOD_SOUND *sound_fire_tank;
FMOD_SOUND *sound_explosion;
FMOD_CHANNEL *canal_bg;
FMOD_CHANNEL *canal_game;

Uint32 previousTimeSoundHelico;

//  world
typedef enum Mode Mode; // direction de l'helico
enum Mode
{
    EASY, MEDIUM, HARD
};

bool gameOver;
bool winner;
Mode mode;

#endif // GLOBALS_H_INCLUDED