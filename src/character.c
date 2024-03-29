/**
 * @file character.c
 * @author Maelig Pesantez
 * @brief character.c is used for it's functions concerning 
 *        the character and it's PV and other specs, from creation to destruction
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "../lib/character.h"

/// @brief Function create is used to create a character by giving a pointer enough memory to point a structure
/// @param c 
void create(character_t ** c, int const nb_pv) {
   *c = malloc(sizeof(character_t));
   (*c)->pv = nb_pv; 
   (*c)->damage = 10;
}

/// @brief Function destruct is used to destruct a character by freeing it's pointer and make it point on NULL
/// @param c 
void destruct(character_t ** c){
   free(*c);
   *c = NULL;
}

/// @brief Function attack is used by "character_t * c" to attack the ennemy (character_t * e).
/// @param c 
/// @param e 
void attack(character_t * c, character_t * e){
   pv_loss(&c, e->damage);
}

/// @brief Function pv_loss is used to make the character lose a certain amount of PV given by int a
/// @param c 
/// @param a 
void pv_loss(character_t ** c, int a){
   (*c)->pv -= a;
   if((*c)->pv < 0){
      (*c)->pv = 0;
   }
}

/// @brief Function pv_gain is used to make the character gain a certain amount of PV given by int a
/// @param c 
/// @param a 
void pv_gain(character_t ** c, int a){
   (*c)->pv += a;
   if((*c)->pv < 0){
      (*c)->pv = 0;
   }
}