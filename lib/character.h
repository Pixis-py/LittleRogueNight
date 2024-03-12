/**
 * @file character.h
 * @author Maelig Pesantez
 * @brief character.h contains the functions's prototypes used in character.c
 *        and the structure character_t
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct character_s character_t;

/// @brief Structure charcter_t is used to stock the character's infomrations
typedef struct character_s{
   int pv;
}character_t;

/// @brief Prototype of function create which is used to create a character by giving a pointer enough memory to point a structure
/// @param c 
void create(character_t ** c);

/// @brief Prototype of function destruct which is used to destruct a character by freeing it's pointer and make it point on NULL
/// @param c 
void destruct(character_t * c);

/// @brief Prototype of function pv_loss which is used to make the character lose a certain amount of PV given by int a
/// @param c 
/// @param a 
void pv_loss(character_t ** c, int a);

/// @brief Prototype of function pv_gain which is used to make the character gain a certain amount of PV given by int a
/// @param c 
/// @param a 
void pv_gain(character_t ** c, int a);