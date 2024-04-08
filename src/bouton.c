/**
 * @file bouton.c
 * @author Enzo Desfaudais
 * @brief bouton.c is used to create buttons more easily
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <SDL2/SDL.h>
#include "../lib/bouton.h"


/// @brief aff_bout creates an SDL_RenderCopy of a button with a normal vue and a hoover vue
/// @param renderer 
/// @param bout 
/// @param e 
/// @param img 
/// @param img2 
/// @return 1 or 0
extern
int aff_bout(SDL_Renderer *renderer, SDL_Rect *bout, SDL_Event e, SDL_Texture * img, SDL_Texture * img2){
    if (e.motion.x > bout->x && e.motion.x < bout->x  + bout->w && e.motion.y > bout->y && e.motion.y < bout->y + bout->h) {
        SDL_RenderCopy(renderer,img,NULL,bout);
        if(e.type == SDL_MOUSEBUTTONDOWN){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        SDL_RenderCopy(renderer,img2,NULL,bout);
        return 0;
    }
}
