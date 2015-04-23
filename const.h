#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

// window
#define SCREEN_WIDTH 920
#define SCREEN_HEIGHT 480

#define POSITION_BOTTOM 339 // position du solle de l'helico, des otages et des prisons
#define POSITION_BASE 318

// background
#define BACKGROUND_WIDTH 4526

// helico
#define HELICO_POSITION_NORMAL_RIGHT_X 2
#define HELICO_POSITION_NORMAL_Y 90

#define HELICO_POSITION_RIGHT_X 0
#define HELICO_POSITION_LEFT_X 249
#define HELICO_POSITION_FORWARD_X 498
#define HELICO_POSITION_Y 0
#define HELICO_WIDTH 83
#define HELICO_HEIGHT 72
#define HELICO_IMAGE_MAX (HELICO_WIDTH * 2)
#define TEMP_ANIMATION_HELICO 40
#define TIME_FIRE_HELICO 300

#define HELICO_CENTER_X (HELICO_WIDTH/1.5)
#define HELICO_CENTER_Y (HELICO_HEIGHT/2)

#define HELICO_CENTER 21 // le centre de l'elico (toute la partie qui se pose sur le sole et que la balle peu atteindre)

#define TEMP_ANIMATION_GRAVITY  100
#define ANIMATIOn_TIME 60
#define HP_HELICO_DEFAULT 3
#define POSITION_SAVE_OTAGE 400 // position max pour poser les otages dans la base

// fire
#define FIRE_POSITION_X 347
#define FIRE_POSITION_Y 241
#define FIRE_WIDTH 8
#define FIRE_HEIGHT 8
#define TEMP_ANIMATION_FIRE 100
#define DISTANCE_FIRE_Y 4

// fire Aircraft
#define FIRE_RIGHT_AIRCRAFT_POSITION_X 487
#define FIRE_LEFT_AIRCRAFT_POSITION_X 461
#define FIRE_AIRCRAFT_POSITION_Y 341
#define FIRE_AIRCRAFT_WIDTH 23
#define FIRE_AIRCRAFT_HEIGHT 10
#define TIME_FIRE_AIRCRAFT 500

// tank
#define TANK_POSITION_X 382
#define TANK_POSITION_Y 324
#define TANK_WIDTH 63
#define TANK_HEIGHT 57
#define TIME_FIRE_TANK 600
#define DISTANCE_TANK_FIRE_LEFT 250
#define DISTANCE_TANK_FIRE_RIGHT 250
#define DISTANCE_SPAWN_TANK 300
#define POSITION_MIN_SPAWN_TANK 650
#define NB_TANK_MAX_EASY 2
#define NB_TANK_MAX_MEDIUM 3
#define NB_TANK_MAX_HARD 5

#define POSITION_CANNON_CENTER 15
#define POSITION_TANK_DEFAULT 450 // represente la position du solle du tank (Y)

// otage
#define OTAGE_POSITION_X 679	// position de l'otage dans l'image
#define OTAGE_POSITION_LEFT_Y 166
#define OTAGE_POSITION_RIGHT_Y 208
#define OTAGE_WIDTH 30
#define OTAGE_HEIGHT 42
#define NB_OTAGE_PER_PRISON 16
#define PX_ENTRE_OTAGE_IMAGE 1
#define OTAGE_IMAGE_MAX 927
#define TEMP_ANIMATION_OTAGE  60
#define TIME_SPAWN_OTAGE 300
#define TIME_TURN_OTAGE 5000
#define NB_OTAGE_MINI_WIN 32

// aicraft
#define AIRCRAFT_POSITION_X  206; // position avion dans l'image
#define AIRCRAFT_POSITION_LEFT_Y  472;
#define AIRCRAFT_POSITION_RIGHT_Y  426;
#define AIRCRAFT_WIDTH 79;
#define AIRCRAFT_HEIGHT 43;
#define POSITION_Y_MAX 0 // hauteur max de l'avion
#define POSITION_Y_MIN 150
#define DISTANCE_AIRCRAFT_Y 20
#define TEMP_ANIMATION_AIRCRAFT 100
#define NBR_OTAGE_TO_SPAWN_AIRCRAFT 8
#define DISTANCE_SPAWN_AIRCRAFT 1000
#define TIME_SPAWN_AIRCRAFT 5000
#define NB_AIRCRAFT_MAX_EASY 1
#define NB_AIRCRAFT_MAX_MEDIUM 2
#define NB_AIRCRAFT_MAX_HARD 3

// prison
#define PRISON_POSITION_X 496
#define PRISON_POSITION_Y 165
#define PRISON_WIDTH 142
#define PRISON_HEIGHT 96
#define NB_PRISON 3
#define DISTANCE_PRISON_SPAWN_TANK_LEFT 400
#define DISTANCE_PRISON_SPAWN_TANK_RIGHT 400
#define TIME_SPAWN_TANK 3000

// exploision 
#define EXPLOSION_POSITION_X 881
#define EXPLOSION_POSITION_Y 406
#define EXPLOSION_WIDTH 52
#define EXPLOSION_HEIGHT 118
#define EXPLOSION_IMAGE_MAX 1141
#define TEMP_ANIMATION_EXPLOSION 100

// explosion prison
#define EXPLOSION_PRISON_POSITION_X 519
#define EXPLOSION_PRISON_POSITION_Y 297
#define EXPLOSION_PRISON_WIDTH 92
#define EXPLOSION_PRISON_HEIGHT 105
#define EXPLOSION_PRISON_IMAGE_MAX 960
#define TEMP_ANIMATION_EXPLOSION_PRISON 100

// saucer
#define SAUCER_POSITION_X 6
#define SAUCER_POSITION_Y 166
#define SAUCER_WIDTH 53
#define SAUCER_HEIGHT 31
#define DISTANCE_SAUCER_X 3
#define DISTANCE_SAUCER_Y 12
#define TEMP_ANIMATION_SAUCER 50
#define SAUCER_IMG_MAX 230
#define SAUCER_TOP_COLLISION 14
#define NB_SAUCER_MAX 1
#define TIME_SPAWN_SAUCER_EASY 20000
#define TIME_SPAWN_SAUCER_MEDIUM 15000
#define TIME_SPAWN_SAUCER_HARD 10000
#define DISTANCE_SPAWN_SAUCER 1000
#define NB_OTAGE_FOR_SPAWN_SAUCER 20

// bool
#define TRUE 1
#define	FALSE 0
#define bool short

// speed
#define VITESS_HELICO 0.3
#define VITESS_BACKGROUND 0.4
#define FIRE_SPEED 0.7
#define FIRE_SPEED_TANK 0.3
#define FIRE_SPEED_AIRCRAFT 0.6
#define VITESS_TANK VITESS_HELICO/2
#define VITESS_AIRCRAFT 0.45
#define VITESS_AIRCRAFT_Y 0.2
#define VITESS_OTAGE 0.1
#define VITESS_EXPLOSION 0.28
#define VITESS_SAUCER 0.28
#define GRAVITY 0.15

// keys, même si ce sont des macro, je m'y retrouve pas trop, donc j'ai changer leur noms
#define UP SDLK_w
#define RIGHT SDLK_d
#define DOWN SDLK_s
#define LEFT SDLK_a
#define TURN SDLK_q // changer la direction de l'elico

// menu
#define EASYK SDLK_a
#define MEDIUMK SDLK_2
#define HARDK SDLK_3

// virtual
#define VIRTUAL_KEYS 2
#define SCROLL_LEFT 323
#define SCROLL_RIGHT 234
#define RIGHT_WALL SCREEN_WIDTH/2 + 1
#define LEFT_WALL SCREEN_WIDTH/2 - 1

#define DIRECTION_GAUCHE 0
#define DIRECTION_DROITE 1

// text
#define POSITION_TEXT_OTAGE 20
#define POSITION_TEXT_OTAGE_SUCCOURED 500
#define POSITION_TEXT_HELICO_HP 270
#define POSITION_TEXT_GAME_OVER_X 350
#define POSITION_TEXT_GAME_OVER_Y 170
#define TEXT_GAME_OVER "Game Over"
#define TEXT_WINNER "You Win :D"

#define TIME_DISABLE_MESSAGE 1500

#endif // CONST_H_INCLUDED