#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define VRAI 1
#define FAUX 0
// Dimensions du labyrinthe: N lignes et M colonnes
#define N 30
#define M 35
// Constantes representant le contenu des cases
#define NUIT 0
#define MUR 1
#define TERRE 2
#define TERREVERTE 3

SDL_Renderer * afficher_lab(int lab[N][M], SDL_Window * pWindow);

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