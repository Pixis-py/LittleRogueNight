/**
 * @file file.c
 * @author Clément Lelandais
 * @brief file.c (in french, file=queue) includes every function needed to use queue in an other program
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// Mise en oeuvre d'une file d'entiers par pointeurs
#include "../lib/file.h"
#include <stdlib.h>

/// @brief element structure, used in queues
typedef struct element {int nombre; struct element* suivant;} t_element;
t_element* tete;
t_element* queue;

/// @brief Function initfile initialize a queue
/// @param  void
void initfile(void){
	tete = NULL;
	queue = NULL;
}

/// @brief Function filevide is used to verify if a queue is empty
/// @param  void
/// @return true or false, wether the queue is empty or not
int filevide(void){
	return tete == NULL;
}

/// @brief Function enfiler is used to add an element to the queue
/// @param v 
void enfiler(int v){
	t_element* nouv;

	nouv = malloc(sizeof(t_element));
	nouv->nombre = v;
	nouv->suivant = NULL;
	if(filevide())
		tete = nouv;
	else
		queue->suivant = nouv;
	queue = nouv;
}

/// @brief Function defiler is used to un-queue an element
/// @param v 
void defiler(int* v){
	t_element* premier;

	if(!filevide()){
		premier = tete;
		*v = premier->nombre;
		tete = premier->suivant;
		free(premier);
	}
}
