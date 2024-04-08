/**
 * @file bouton.h
 * @author Enzo Desfaudais
 * @brief bouton.h contains prototypes of functions in bouton.c made to create buttons more easily
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <SDL2/SDL.h>

#define BOUTON_RELACHE 0
#define BOUTON_APPUYE 1
#define BOUTON_DESSUS 2
 
// Structure contenant les informations sur le bouton
/// @brief Structure bouton_s is used to stock the button renderer informations as classic and hoover vue, state, and position
typedef struct bouton_s
{
    SDL_Rect *position; // contient la position (.x et .y) et les dimensions (.w et .h) du bouton
    int etat; // contient l'état du bouton (BOUTON_RELACHE / BOUTON_APPUYE // BOUTON_DESSUS )
    SDL_Texture *dessus; // image du bouton lorsqu'il est relaché
    SDL_Texture *classique; // image du bouton lorsqu'il est appuyé
}bouton;

/// @brief aff_bout prototype, real function creates an SDL_RenderCopy of a button with a normal vue and a hoover vue
/// @param renderer 
/// @param bout 
/// @param e 
/// @param img 
/// @param img2 
/// @return 1 or 0
int aff_bout(SDL_Renderer *renderer,SDL_Rect *bout, SDL_Event e,SDL_Texture * img,SDL_Texture * img2);
