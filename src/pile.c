/**
 * @file pile.c
 * @author Clément Lelandais
 * @brief Pile.c (in french, pile=stack) includes every function needed to use stacks in an other program 
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../lib/pile.h"
#include <stdlib.h>

/// @brief element structs are used in stacks
typedef struct element {char c; struct element * suivant;} t_element;
t_element * pile;

/// @brief Function initpile is used to initialize a stack 
/// @param void
void initpile(void)
{
    // initialise la pile à vide
    pile = NULL;
}

/// @brief Function epmiler is used to add an element to the stack
/// @param c 
void empiler(int c){
// empile la valeur c
    t_element* nouv;
    nouv = malloc(sizeof(t_element));
    nouv->c = c;
    nouv->suivant = pile;
    pile = nouv;
}

/// @brief Function depiler is used to unstack an element from a stack
/// @param c 
void depiler(int * c){
// dépile le sommet et l’affecte à c
    t_element* sommet;
    if (pile!=NULL){
        *c = pile->c;
        sommet = pile;
        pile = sommet->suivant;
        free(sommet);
    }
}

/// @brief Function pilevide is used to know if a stack is empty
/// @param  void
/// @return true or false wether the satck is empty or not
int pilevide(void)
{
    // délivre vrai si la pile est vide
    return (pile == NULL);
}

/// @brief Function sommetpile is used to know stack's top
/// @param c 
void sommetpile(int *c)
{
    // délivre le sommet de pile sans dépiler
    if (pile != NULL)
    {
        *c = pile->c;
    }
}
