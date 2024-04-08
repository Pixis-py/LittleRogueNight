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
#define N LARGEUR * 5
#define M LONGUEUR * 5


SDL_Renderer * afficher_lab(int lab[N][M], SDL_Window * pWindow);

void affichage_laby_niveau_un(int lab[N][M], int posi, int posj, SDL_Renderer * pRenderer);

void init_lab(int lab[N][M]);

//******************************
// Partie creation du labyrinthe
//******************************

int valides(int i, int j);

int est_NUIT(int i, int j, int lab[N][M]);

int est_MUR(int i, int j, int lab[N][M]);

int vide(int i, int j, int lab[N][M]);

void creer_lab(int lab[N][M]);

int labyrinthe();

int chercher_chemin(const int lab[N][M], int id, int jd, int ia, int ja);
