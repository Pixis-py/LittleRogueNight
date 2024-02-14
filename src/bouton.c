#include <SDL2/SDL.h>
#include "../lib/bouton.h"


extern
int aff_bout(SDL_Renderer *renderer,SDL_Rect *bout, SDL_Event e,SDL_Texture * img,SDL_Texture * img2){
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