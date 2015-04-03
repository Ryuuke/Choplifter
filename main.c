#include "initialize.h"
#include "game.h"   
#include "timers.h"
#include "globals.h"

int main(int argc, char *argv[])
{   
    // initialisation des variables
    initAll();
    
    // boucle du jeu
    game();
    
    // netoyage de la memoire et fermeture du programme
    quit();
    
    return EXIT_SUCCESS;
}