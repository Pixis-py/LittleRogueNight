/**
 * @file labyrinthe.c
 * @author Clément Lelandais (you@domain.com)
 * @brief File made to manage labyrinth
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// TP4 - Recherche du chemin le plus court avec une file
#include "../lib/labyrinthe.h"
#include "../lib/image.h"
#include "../lib/file.h"
#include "../lib/pile.h"

/// @brief Function affichage_laby_niveau_un purpose is to render the lab with the correct tiles (grass and dirt here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_un(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY){
	SDL_Texture* pSkyTexture = loadTexture("../sprites/tiles/night_sky.png", pRenderer);
    SDL_Texture* pGrassTexture = loadTexture("../sprites/tiles/grass.png", pRenderer);	
    SDL_Texture* pDirtTexture = loadTexture("../sprites/tiles/dirt.png", pRenderer);
    
    if (pSkyTexture != NULL && pGrassTexture != NULL && pDirtTexture != NULL){
        for (int i = 0; i <= M + 1; i++) {
            SDL_Rect rect = { ((i - coefX) ) * FORMATPIXELZOOM, (-coefY ) * FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pGrassTexture, NULL, &rect);
        }
        
        for (int i = 0; i < N; i++) {
            SDL_Rect rect = { (-coefX ) * FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pDirtTexture, NULL, &rect);
            for (int j = 0; j < M; j++) {
                SDL_Rect rect = { ((j - coefX) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
                switch (lab[i][j]) {
                    case NUIT:
                        SDL_RenderCopy(pRenderer, pSkyTexture, NULL, &rect);
                        break;
                    case TERREVERTE:
                        SDL_RenderCopy(pRenderer, pGrassTexture, NULL, &rect);
                        break;  
                    case TERRE:
                        SDL_RenderCopy(pRenderer, pDirtTexture, NULL, &rect);
                        break;
                }
            }
            SDL_Rect rect1 = { ((M - coefX)) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY)) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pDirtTexture, NULL, &rect1);
        }
        for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				if(lab[i][j] == TERREVERTE && (lab[i - 1][j] == TERREVERTE || lab[i - 1][j] == TERRE || i == 0))
					lab[i][j] = TERRE;
			}
		}
    }
	SDL_DestroyTexture(pSkyTexture);
	SDL_DestroyTexture(pDirtTexture);
    SDL_DestroyTexture(pGrassTexture);
}

/// @brief Function affichage_laby_niveau_deux purpose is to render the lab with the correct tiles (wood here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_deux(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY){
	SDL_Texture* pSkyTexture = loadTexture("../sprites/tiles/night_sky.png", pRenderer);
    SDL_Texture* pWoodTexture = loadTexture("../sprites/tiles/wood_planks.png", pRenderer);	
    
    if (pSkyTexture != NULL && pWoodTexture != NULL){
        for (int i = 0; i <= M + 1; i++) {
            SDL_Rect rect = { ((i - coefX) ) * FORMATPIXELZOOM, (-coefY ) * FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pWoodTexture, NULL, &rect);
        }
        
        for (int i = 0; i < N; i++) {
            SDL_Rect rect = { (-coefX ) * FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pWoodTexture, NULL, &rect);
            for (int j = 0; j < M; j++) {
                SDL_Rect rect = { ((j - coefX) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
                switch (lab[i][j]) {
                    case NUIT:
                        SDL_RenderCopy(pRenderer, pSkyTexture, NULL, &rect);
                        break;
                    case TERREVERTE:
                        SDL_RenderCopy(pRenderer, pWoodTexture, NULL, &rect);
                        break;
                    case TERRE:
                        SDL_RenderCopy(pRenderer, pWoodTexture, NULL, &rect);
                        break;
                }
            }
            SDL_Rect rect1 = { ((M - coefX)) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY)) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pWoodTexture, NULL, &rect1);
        }
        for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				if(lab[i][j] == TERREVERTE && (lab[i - 1][j] == TERREVERTE || lab[i - 1][j] == TERRE || i == 0))
					lab[i][j] = TERRE;
			}
		}
		SDL_DestroyTexture(pSkyTexture);
		SDL_DestroyTexture(pWoodTexture);
    }
}

/// @brief Function affichage_laby_niveau_trois purpose is to render the lab with the correct tiles (brics here)
/// @param lab
/// @param pRenderer
/// @param coefX
/// @param coefY
void affichage_laby_niveau_trois(int lab[N][M], SDL_Renderer * pRenderer, int coefX, int coefY){
	SDL_Texture* pSkyTexture = loadTexture("../sprites/tiles/night_sky.png", pRenderer);
    SDL_Texture* pBrickTexture = loadTexture("../sprites/tiles/brick.png", pRenderer);	
    
    if (pSkyTexture != NULL && pBrickTexture != NULL){
        for (int i = 0; i <= M + 1; i++) {
            SDL_Rect rect = { ((i - coefX) ) * FORMATPIXELZOOM, (-coefY ) * FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pBrickTexture, NULL, &rect);
        }
        
        for (int i = 0; i < N; i++) {
            SDL_Rect rect = { (-coefX ) * FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pBrickTexture, NULL, &rect);
            for (int j = 0; j < M; j++) {
                SDL_Rect rect = { ((j - coefX) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY) ) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
                switch (lab[i][j]) {
                    case NUIT:
                        SDL_RenderCopy(pRenderer, pSkyTexture, NULL, &rect);
                        break;
                    case TERREVERTE:
                        SDL_RenderCopy(pRenderer, pBrickTexture, NULL, &rect);
                        break;
                    case TERRE:
                        SDL_RenderCopy(pRenderer, pBrickTexture, NULL, &rect);
                        break;
                }
            }
            SDL_Rect rect1 = { ((M - coefX)) * FORMATPIXELZOOM + FORMATPIXELZOOM, ((i - coefY)) * FORMATPIXELZOOM + FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM };
            SDL_RenderCopy(pRenderer, pBrickTexture, NULL, &rect1);
        }
        for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				if(lab[i][j] == TERREVERTE && (lab[i - 1][j] == TERREVERTE || lab[i - 1][j] == TERRE || i == 0))
					lab[i][j] = TERRE;
			}
		}
		SDL_DestroyTexture(pSkyTexture);
		SDL_DestroyTexture(pBrickTexture);
    }
}

/// @brief Function init_lab purpose is to init the matrix used to create the labyrinth
/// @param lab
void init_lab(int lab[N][M]){
	//1ère étape pour la création du labyrinthe parfat : tout initialiser en bloc de terre (avec du vert au dessus)
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++)
			lab[i][j] = TERREVERTE;		
	}
}

/// @brief Function valides purpose is to return true or false if coordonates are correct (in the matrix)
/// @param i
/// @param j
int valides(int i, int j){
// renvoie 1 si i et j se trouve sur une case du labyrinthe
	return(i >= 0 && i < N && j >= 0 && j < M);
}

/// @brief Function est_NUIT purpose is to return true if coordonates in the matrix are empty (night = NUIT)
/// @param i
/// @param j
/// @param lab
int est_NUIT(int i, int j, int lab[N][M]){
	return(valides(i, j) && lab[i][j] == NUIT);
}

/// @brief Function est_TERRE purpose is to return true if coordonates in the matrix are full (dirt = TERRE)
/// @param i
/// @param j
/// @param lab
int est_TERRE(int i, int j, int lab[N][M]){
	return(valides(i, j) && (lab[i][j] == TERREVERTE || lab[i][j] == TERRE));
}

/// @brief Function est_NUIT purpose is to return true if coordonates in the matrix are empty
/// @param i
/// @param j
/// @param lab
int vide(int i, int j, int lab[N][M]){
//Aucune case voisine n'est une terre
	return (!est_TERRE(i + 2, j, lab) && !est_TERRE(i - 2, j, lab) && !est_TERRE(i, j + 2, lab) && !est_TERRE(i, j - 2, lab));
}

/// @brief Function creer_lab purpose is to create the perfect labyrinth randomly using an initialized matrix
/// @param lab
void creer_lab(int lab[N][M]){
//2ème étape : création du labyrinthe selon un algorithme utilisant une pile

	int termine = FAUX;
	int trouve = FAUX;
	int i, j, alea;

	init_lab(lab);
	initpile();

	i = 0, 
	j = 0;
	lab[0][0] = NUIT;

   while(!termine){

	if(vide(i, j, lab)){
		if(!pilevide()){
			depiler(&j);
			depiler(&i);
		}
		else
			termine = VRAI;
	}
	else{
		trouve = FAUX;
		while(!trouve){
			alea = rand() % 4; 
			switch(alea){
				case 0: 
					if(est_TERRE(i + 2, j, lab)){ 
						empiler(i);
						empiler(j);
						lab[i + 1][j] = NUIT;
						lab[i + 2][j] = NUIT;
						i +=  2;
						trouve = VRAI;
						break;
					}	
				case 1: 	
					if(est_TERRE(i - 2, j, lab)){
						empiler(i);
						empiler(j);
						lab[i - 1][j] = NUIT;
						lab[i - 2][j] = NUIT;
						i -= 2;
						trouve = VRAI;
						break;
					}	
				case 2: 	
					if(est_TERRE(i, j + 2, lab)){
						empiler(i);
						empiler(j);
						lab[i][j + 1] = NUIT;
						lab[i][j + 2] = NUIT;
						j += 2;
						trouve = VRAI;
						break;
					}	
				case 3: 	
					if(est_TERRE(i, j - 2, lab)){
						empiler(i);
						empiler(j);
						lab[i][j - 1] = NUIT;
						lab[i][j - 2] = NUIT;
						j -= 2;
						trouve = VRAI;
					}	
			}
		}
	}
   }
}

//***************************
// Partie recherche de chemin
//***************************

/// @brief Function chercher_chemin purpose is to true if the labyrinth is perfect and has a correct path from start to end
/// @param lab
/// @param id
/// @param jd
/// @param ia
/// @param ja
int chercher_chemin(const int lab[N][M], int id, int jd, int ia, int ja){
    //3ème étape : Vérification du labyrinthe (si un chemin existe alors il est parfait)
    //Cherche le chemin D -> A le plus court avec une file en prenant un autre labyrinthe en copie pour pas modifier le labyrinthe actuel
    int i, j, temp[N][M], k;
    initfile();
	memcpy(temp, lab, sizeof(temp));
    temp[id][jd] = 1;
	enfiler(id); 
	enfiler(jd);
    do{
        defiler(&i);
        defiler(&j);
        k = lab[i][j];
        if(est_NUIT(i - 1, j, temp)){
            temp[i - 1][j] = k + 1;
            enfiler(i - 1);
            enfiler(j);
        }
        if(est_NUIT(i + 1, j, temp)){
            temp[i + 1][j] = k + 1;
            enfiler(i + 1);
            enfiler(j);
        }
        if(est_NUIT(i, j - 1, temp)){
            temp[i][j - 1] = k + 1;
            enfiler(i);
            enfiler(j - 1);
        }
        if(est_NUIT(i, j + 1, temp)){
            temp[i][j + 1] = k + 1;
            enfiler(i);
            enfiler(j + 1);
        }
    }while (((i != ia) || (j != ja))&& !filevide());
    return (i == ia && j == ja);
}
