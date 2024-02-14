#include <stdlib.h>
#include <stdio.h>
#include "../lib/anim.h"
#include "../lib/image.h"
#include "../lib/labyrinthe.h"

int menu(int argc, char** argv);

int main(){
    int choice;
    printf("Program launch...\n");
    //choice = menu(0, NULL); // Lancement du menu
    int lab[N][M];
    creer_lab(lab);
    printf("\n\nle lab est crée\n\n");
    if(chercher_chemin(lab, N - 1, M - 1, 0, 0))
    printf("\n\non rentre dans le lab\n\n");
        anim(0, NULL, lab); // Boucle de jeu (labyrinthe et animation)
    printf("Program exit...\n");
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé normalement
}



int menu(int argc, char** argv){

/* ----------------------------------------------------- Initialisation ----------------------------------------------------- */


/* ----------------------------------------------------- Création et gestion de la fenêtre SDL ----------------------------------------------------- */

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 ){
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    else{
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("LittleRogueNight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        	fprintf(stderr, "Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        	SDL_Quit();
        	return 1;
    	}
        if( pWindow )
        {

/* ----------------------------------------------------- Chargement et positionnement des sprites ----------------------------------------------------- */

            SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle
            if ( pRenderer ){

                SDL_Texture* pTextureMenuWallpaper =loadTexture("../Sprites/Menu/menuWallpaper.png",pRenderer);
                SDL_Texture* pTexturePlayButton =loadTexture("../Sprites/Menu/play.png",pRenderer);

                if ( pTextureMenuWallpaper != NULL){


                        SDL_Rect menuWallpaper= {0,0, 1280, 720};
                        SDL_Rect playButton= {510, 310, 260, 100};
                        
                        //declaration de quit la variable booleene qui met fin a la boucle
                        int quit = 0;
                        
                        //boucle du jeux

                        SDL_Event event;

/* ----------------------------------------------------- Détection des frappes ----------------------------------------------------- */

                        while (!quit) {


/* ----------------------------------------------------- Animation ----------------------------------------------------- */
                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    quit = 1;
                                }
                            }

                            SDL_RenderCopy(pRenderer,pTextureMenuWallpaper, NULL, &menuWallpaper);
                            SDL_RenderCopy(pRenderer,pTexturePlayButton, NULL, &playButton);
                            SDL_RenderPresent(pRenderer); // Affichage
                            SDL_Delay(1000);
                            SDL_RenderPresent(pRenderer);
                        }

                        SDL_DestroyTexture(pTextureMenuWallpaper); // Libération de la mémoire associée à la texture
                    }
                    else
                    {
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                    }
        
                    
    
                SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
            }
            else
            {
                fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
            }
            SDL_Delay(10000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
            SDL_DestroyWindow(pWindow);
        }
     else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();
    IMG_Quit();

    return 0;
}