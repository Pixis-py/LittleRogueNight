#include <stdio.h>

#include "../lib/labyrinthe.h"
#include "../lib/anim.h"
#include "../lib/image.h"


int anim(int argc, char** argv, int lab[N][M]){

/* ----------------------------------------------------- Initialisations ----------------------------------------------------- */

	int i = 0, j = 0, k = 0; // Initialisation des compteurs pour les boucles d'animation
    int x = 0, y = 0, w = 0 , h = 0; // Initialisation des coordonnées communes à chaque animation
    int lastKeyPressed; // Variable de la dernière touche préssée
    int lkpshift; // Vaut 1 si la dernière combinaison comprenait shift (donc un drift)
    int lkpdash; // Vaut 1 si la dernière combinaison comprenait espace (donc un dash)
    int lastDirection = 1; // Vaut 1 ou 2 selon la dernière direction

/* ----------------------------------------------------- Création et gestion de la fenêtre SDL ----------------------------------------------------- */


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 ){
        
        // Boucle si erreur lors de la création de la fenêtre (retournant le code -1)
        fprintf(stdout,"Échec de l'initialisation de la fenêtre SDL (%s)\n",SDL_GetError());
        return -1;

    }

    else{
        
        // Création de la fenêtre
        SDL_Window * pWindow = NULL;
        pWindow = SDL_CreateWindow("LittleRogueNight_jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LONGUEUR * FORMATPIXELZOOM + FORMATPIXELZOOM, LARGEUR * FORMATPIXELZOOM + FORMATPIXELZOOM, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
            // Boucle si erreur lors de l'initialisation de SDL_image (retournant le code 1)
        	fprintf(stderr, "Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        	SDL_Quit();
        	return 1;

    	}

        if( pWindow )
        {
/* ----------------------------------------------------- Chargement et positionnement des Sprites ----------------------------------------------------- */


            SDL_Renderer * pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

            if ( pRenderer ){
                //sprites
                SDL_Texture* pTextureRun = loadTexture("../sprites/six/six_run.png", pRenderer);
                SDL_Texture* pTextureDrift = loadTexture("../sprites/six/six_drift.png", pRenderer);
                SDL_Texture* pTextureDash = loadTexture("../sprites/six/six_dash.png", pRenderer);
                //fonction d'affichage des animations des sprites
                if ( pTextureRun != NULL && pTextureDrift != NULL && pTextureDash != NULL){
                        SDL_Rect position = {FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM};
                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de marche*/
                        SDL_Rect run[11] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                        for (i=0;i<11;i++){
                            run[i].x=x;
                            run[i].y=0;
                            run[i].w=FORMATPIXEL;
                            run[i].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de drift*/

                        SDL_Rect drift[24] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                        for (j=0;j<24;j++){
                            drift[j].x=x;
                            drift[j].y=0;
                            drift[j].w=FORMATPIXEL;
                            drift[j].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;
                        j=-1;

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de dash*/

                        SDL_Rect dash[20] = { 0,0, FORMATPIXEL,FORMATPIXEL};
                        for (k=0;k<20;k++){
                            dash[k].x=x;
                            dash[k].y=0;
                            dash[k].w=FORMATPIXEL;
                            dash[k].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;
                        k=-1;
                        
                        SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position); //copie du personnage dans sa position de base
                        SDL_RenderPresent(pRenderer); // Affichage
                        
                        // declaration de event pour récuperer les evenement
                        SDL_Event event;
                        SDL_Event event2;
                        
                        //declaration de quit etant la variable booleen qui met fin a la boucle
                        //declaration keyPressed pour gérer si une touche est maintenu ou relacher
                        int quit = 0, KeyIsPressed=0;
                        
                        //boucle du jeu

/* ----------------------------------------------------- Détection des frappes ----------------------------------------------------- */

                        while (!quit){
                            printf("Total :\nx = %d\t\ty = %d\nPrécis :\nx = %d\t\ty = %d\n\n", 
                            position.x, position.y, 
                            position.x % FORMATPIXEL, position.y % FORMATPIXEL);
                            affichage_laby_niveau_un(lab, position.y, position.x, pRenderer);
                            // récuperation du clic sur le bouton de fermeture et met fin a la boucle
                            while (SDL_PollEvent(&event) != 0){
                                if (event.type == SDL_QUIT){
                                    quit = 1;
                                }

                                // Récuperation des frappes
                                if (event.type == SDL_KEYDOWN) {
                                    
                                    /*------------------------------ Run -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_d) {
                                        if (KeyIsPressed == 0 || KeyIsPressed == -1) {
                                            KeyIsPressed = 1;
                                            lastKeyPressed = 1;
                                            lastDirection = 1;
                                        }  
                                    }
                                    else if (event.key.keysym.sym == SDLK_q) {
                                        if (KeyIsPressed == 0 || KeyIsPressed == -1) {
                                            KeyIsPressed = 2;
                                            lastKeyPressed = 2;
                                            lastDirection = 2;
                                        }  
                                    }
                                    /*else if (event.key.keysym.sym == SDLK_d && event.key.keysym.sym == SDLK_q){       EVENT2, PAS POUR LE MOMENT
                                        if(KeyIsPressed == 0 || KeyIsPressed == -1){
                                            KeyIsPressed = 9;
                                        }
                                    }*/

                                    /*------------------------------ Drift -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_LSHIFT && lastKeyPressed == 2){
                                        if (KeyIsPressed == 1 || KeyIsPressed == 2) {
                                            KeyIsPressed = 3;
                                            lkpshift = 1;
                                            lastDirection = 1;
                                        }  
                                    }
                                    if (event.key.keysym.sym == SDLK_LSHIFT && lastKeyPressed == 1){
                                        if (KeyIsPressed == 1 || KeyIsPressed == 2) {
                                            KeyIsPressed = 4;
                                            lkpshift = 2;
                                            lastDirection = 2;
                                        }  
                                    }

                                    /*------------------------------ Dash -------------------------------*/

                                    /*if (event.key.keysym.sym == SDLK_SPACE && lastKeyPressed == 2){
                                        if (KeyIsPressed == 1 || KeyIsPressed == 2) {
                                            KeyIsPressed = 5;
                                            lkpdash = 1;
                                            lastDirection = 1;
                                        }  
                                    }
                                    else if (event.key.keysym.sym == SDLK_SPACE && lastKeyPressed == 1){
                                        if (KeyIsPressed == 1 || KeyIsPressed == 2) {
                                            KeyIsPressed = 6;
                                            lkpdash= 2;
                                            lastDirection = 2;
                                        }  
                                    }*/
                                    if (event.key.keysym.sym == SDLK_SPACE && lastDirection == 1){
                                        KeyIsPressed = 7;
                                        lkpdash= 1;
                                    }
                                    else if (event.key.keysym.sym == SDLK_SPACE && lastDirection == 2){
                                        KeyIsPressed = 8;
                                        lkpdash= 2;
                                    }
                                }
                                
                                // Récuperation des touche relachées
                                else if (event.type == SDL_KEYUP) {
                                    if (event.key.keysym.sym == SDLK_q){
                                        KeyIsPressed = 0;
                                    }
                                    else if(event.key.keysym.sym == SDLK_d){
                                        KeyIsPressed = -1;
                                        lastKeyPressed = -1;
                                    }
                                    else if(lkpshift == 1){
                                        KeyIsPressed = 0;
                                        j = -1;
                                    }
                                    else if(lkpshift == 2){
                                        KeyIsPressed = -1;
                                        j = -1;
                                    }
                                    else if(lkpdash == 1){
                                        KeyIsPressed = 0;
                                    }
                                    else if(lkpdash == 2){
                                        KeyIsPressed = -1;
                                    }
                                }
                            }

/* ----------------------------------------------------- Animation ----------------------------------------------------- */
                            /*------------------------------ Run -------------------------------*/

                            // Affichage run à droite (/ 9 = zoom²)
                            int gravite = (lab[(position.y / FORMATPIXELZOOM / 9)][(position.x / FORMATPIXELZOOM / 9) - 1] == DUR
                                        && lab[(position.y / FORMATPIXELZOOM / 9)][(position.x / FORMATPIXELZOOM / 9)] == (NUIT || DUR)
                                        && (position.x + FORMATPIXEL / 2 % FORMATPIXEL) >= 20)

                                        || lab[(position.y / FORMATPIXELZOOM / 9)][(position.x / FORMATPIXELZOOM / 9) - 1] == NUIT

                                        || (lab[(position.y / FORMATPIXELZOOM / 9)][(position.x / FORMATPIXELZOOM / 9) - 1] == DUR
                                        && lab[(position.y / FORMATPIXELZOOM / 9)][(position.x / FORMATPIXELZOOM / 9) - 2] == (NUIT || DUR)
                                        && (position.x % FORMATPIXEL) >= 6);
                            if(gravite)
                                position.y += 2 * ZOOM;

                            if(KeyIsPressed == 1){
                                //if(caseijplusun != TERREVERTE || caseijplusun != TERRE)
                                    position.x += 2 * ZOOM;
                                SDL_RenderCopy(pRenderer,pTextureRun,run+((++i)%11),&position);
                            }

                            // Affichage run à gauche
                            if(KeyIsPressed==2){
                                //if(caseijplusun != TERREVERTE || caseijplusun != TERRE)
                                    position.x-=2 * ZOOM;
                                SDL_RenderCopyEx(pRenderer,pTextureRun,run+((++i)%11),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                            }

                            /*------------------------------ Statique -------------------------------*/

                            // Affichage statique gauche
                            else if(KeyIsPressed==0 && lastDirection == 1){
                                SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position);

                            }
                            
                            // Affichage statique droite
                            else if(KeyIsPressed==0 && lastDirection == 2){
                                SDL_RenderCopyEx(pRenderer,pTextureRun,run+0,&position, 0, NULL, SDL_FLIP_HORIZONTAL);// Affichage statique
                            }

                            /*------------------------------ Drift -------------------------------*/

                            // Affichage drift gauche
                            else if(KeyIsPressed==3){
                                //if(caseijplusun != TERREVERTE || caseijplusun != TERRE)
                                    position.x-=2 * ZOOM;
                                if(j == 23){
                                    SDL_RenderCopyEx(pRenderer,pTextureDrift,drift+((23)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }else{
                                    SDL_RenderCopyEx(pRenderer,pTextureDrift,drift+((++j)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                            }

                            // Affichage drift gauche
                            else if(KeyIsPressed==4){
                                //if(caseijplusun != TERREVERTE || caseijplusun != TERRE)
                                    position.x+=2 * ZOOM;
                                if(j == 23){
                                    SDL_RenderCopy(pRenderer,pTextureDrift,drift+((23)),&position);
                                }else{
                                    SDL_RenderCopy(pRenderer,pTextureDrift,drift+((++j)),&position);
                                }
                            }

                            /*------------------------------ Dash -------------------------------*/

                            // Affichage dash gauche
                            /*else if(KeyIsPressed==5){
                               
                                if(k<=4){
                                    position.x-=6;
                                    SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                                else if(k<=6){
                                    position.x-=15;
                                    position.y-=20;
                                    SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                                else if(k<=9){
                                    position.x-=15;
                                    SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                                else if(k<=11){
                                    position.x-=15;
                                    position.y+=20;
                                    SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }else if(k > 15){
                                    position.x-=6;
                                    SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                                
                                if(k == 20){
                                    KeyIsPressed = 0;
                                    k = 0;
                                }
                            }*/

                            // Affichage dash droite
                            /*else if(KeyIsPressed==6){
                                //SDL_RenderClear(pRenderer);
                                if(k<=4){
                                    position.x+=6;
                                    SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)),&position);
                                }
                                else if(k<=6){
                                    position.x+=20;
                                    position.y-=30;
                                    //SDL_Delay(10);
                                    SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)),&position);
                                }else if(k<=11){
                                    position.x+=20;
                                    position.y+=30;
                                    //SDL_Delay(10);
                                    SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)),&position);
                                }else if(k > 15){
                                    position.x+=6;
                                    SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)),&position);
                                }
                    
                                if(k == 20){
                                    KeyIsPressed = 0;
                                    k = 0;
                                }
                            }*/

                            // Affichage dash statique à droite
                            else if(KeyIsPressed==7){
                                //if(caseiplusunj != TERREVERTE || caseiplusunj != TERRE)
                                    position.y-=10 * ZOOM;
                                //SDL_Delay(10);
                                SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)%20),&position);
                            }

                            // Affichage dash statique à gauche
                            else if(KeyIsPressed==8){
                                //if(caseiplusunj != TERREVERTE || caseiplusunj != TERRE)
                                    position.y-=10 * ZOOM;
                                //SDL_Delay(10);
                                SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)%20),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                            }
                        
                            
                            /*------------------------------ Default -------------------------------*/
 
                            else{
                                if(lastDirection == 1){
                                    SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position);
                                     // Affichage défaut   
                                }else{
                             
                                    SDL_RenderCopyEx(pRenderer,pTextureRun,run+0,&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                // Affichage défaut   
                                }
                                
                            }
                        

                            SDL_Delay(30); // Délai générique à toutes les animations
                            SDL_RenderPresent(pRenderer); // Affichage du Renderer
                        }

/* ----------------------------------------------------- Libération de la mémoire des textures ----------------------------------------------------- */

                        SDL_DestroyTexture(pTextureRun);
                        SDL_DestroyTexture(pTextureDrift);
                        SDL_DestroyTexture(pTextureDash);
                    
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
            SDL_Delay(1000); // Attente pour le chargement de la page
            SDL_DestroyWindow(pWindow); // Libération de la mémoire de la fenêtre SDL
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
