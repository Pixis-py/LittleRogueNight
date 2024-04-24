/**
 * @file anim.h
 * @author Clément Lelandais Maelig Pesantez Enzo Desfaudais
 * @brief 
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "image.h"
#include "character.h"

/**
 * @brief Prototype of function creer_coord which generate valid coordonates randomly and assign them to the entity 
 * 
 * @param ent 
 * @param lab 
 */
void creer_coord(character_t ** ent, int lab[N][M]);

/**
 * @brief Main function which uses to manage Six's animations, therefore movements, collisions and also entity management from coordonates given by the creer_coord function
 * 
 * @param argc 
 * @param argv 
 * @param lab 
 * @param niveau 
 * @param player 
 * @return int 
 */
int anim(int argc, char** argv, int lab[N][M], int niveau, character_t ** player);

