/**
 * @file labyrinthe.h
 * @author Clement Lelandais (you@domain.com)
 * @brief This files contains every function prototype and consts used in labyrinthe.c
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define VRAI 1
#define FAUX 0
// Constantes representant le contenu des cases
#define NUIT 0
#define MUR 1
#define TERRE 2
#define TERREVERTE 3
#define DUR TERRE || TERREVERTE
//labyrinthe
#define FORMATPIXEL 32
#define ZOOM 3
#define FORMATPIXELZOOM FORMATPIXEL * ZOOM
#define LARGEUR 7
#define LONGUEUR 10
#define N LARGEUR * 5 + 7
#define M LONGUEUR * 5 + 9


SDL_Renderer * afficher_lab(int lab[N][M], SDL_Window * pWindow);

/// @brief Function affichage_laby_niveau_un purpose is to render the lab with the correct tiles (grass and dirt here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_un(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY);

/// @brief Function affichage_laby_niveau_deux purpose is to render the lab with the correct tiles (wood here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_deux(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY);

/// @brief Function affichage_laby_niveau_trois purpose is to render the lab with the correct tiles (brics here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_trois(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY);

/// @brief Function init_lab purpose is to init the matrix used to create the labyrinth
/// @param lab
void init_lab(int lab[N][M]);

//******************************
// Partie creation du labyrinthe
//******************************

/// @brief Function valides purpose is to return true or false if coordonates are correct (in the matrix)
/// @param i
/// @param j
int valides(int i, int j);

/// @brief Function est_NUIT purpose is to return true if coordonates in the matrix are empty (night = NUIT)
/// @param i
/// @param j
/// @param lab
int est_NUIT(int i, int j, int lab[N][M]);

/// @brief Function est_TERRE purpose is to return true if coordonates in the matrix are full (dirt = TERRE)
/// @param i
/// @param j
/// @param lab
int est_TERRE(int i, int j, int lab[N][M]);

/// @brief Function est_NUIT purpose is to return true if coordonates in the matrix are empty
/// @param i
/// @param j
/// @param lab
int vide(int i, int j, int lab[N][M]);

/// @brief Function creer_lab purpose is to create the perfect labyrinth randomly using an initialized matrix
/// @param lab
void creer_lab(int lab[N][M]);

/// @brief Function chercher_chemin purpose is to true if the labyrinth is perfect and has a correct path from start to end
/// @param lab
/// @param id
/// @param jd
/// @param ia
/// @param ja
int chercher_chemin(const int lab[N][M], int id, int jd, int ia, int ja);
