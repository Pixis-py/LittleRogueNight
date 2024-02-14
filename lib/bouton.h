#include <SDL2/SDL.h>

#define BOUTON_RELACHE 0
#define BOUTON_APPUYE 1
#define BOUTON_DESSUS 2
 
// Structure contenant les informations sur le bouton
typedef struct bouton_s
{
    SDL_Rect *position; // contient la position (.x et .y) et les dimensions (.w et .h) du bouton
    int etat; // contient l'état du bouton (BOUTON_RELACHE / BOUTON_APPUYE // BOUTON_DESSUS )
    SDL_Texture *dessus; // image du bouton lorsqu'il est relaché
    SDL_Texture *classique; // image du bouton lorsqu'il est appuyé
}bouton;


int aff_bout(SDL_Renderer *renderer,SDL_Rect *bout, SDL_Event e,SDL_Texture * img,SDL_Texture * img2);