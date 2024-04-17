#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../lib/labyrinthe.h"

#define FONT_PATH "arial.ttf"

int anim(int argc, char** argv, int lab[N][M], int niveau);

int message_joueur(const char * text, int x, int y, SDL_Window * pWindow);
