#include "../lib/pile.h"
#include <stdlib.h>

typedef struct element {char c; struct element * suivant;} t_element;
t_element * pile;

void initpile(void)
{
    // initialise la pile à vide
    pile = NULL;
}

void empiler(int c){
// empile la valeur c
    t_element* nouv;
    nouv = malloc(sizeof(t_element));
    nouv->c = c;
    nouv->suivant = pile;
    pile = nouv;
}

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

int pilevide(void)
{
    // délivre vrai si la pile est vide
    return (pile == NULL);
}

void sommetpile(int *c)
{
    // délivre le sommet de pile sans dépiler
    if (pile != NULL)
    {
        *c = pile->c;
    }
}
