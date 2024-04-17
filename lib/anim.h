#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "image.h"
#include "character.h"

#define FONT_PATH "arial.ttf"

void creer_coord(character_t ** ent, int lab[N][M]);

int anim(int argc, char** argv, int lab[N][M], int niveau, character_t ** player);

int message_joueur(const char * text, int x, int y, SDL_Window * pWindow);
