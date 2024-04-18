#include <stdio.h>
#include <stdlib.h>

#include "../lib/anim.h"


void creer_coord(character_t ** ent, int lab[N][M]){
    int x, y;
    int i, j;
    int possible=0;
    x = rand() % N;
    
    while(!possible){
        x = rand() % N;
        for(i=0;i<M;i++){
            if(lab[x][i]==0 && lab[x+1][i]==3){
                possible=1;
            }
        }
    }
    possible=0;
    while(!possible){
        y = rand() % M;
        if(lab[x][y]==0 && lab[x+1][y]==3){
            possible=1;
        }
    }

    (*ent)->x = y+1;
    (*ent)->y = x+1;
}

int message_joueur(const char * text, int x, int y, SDL_Window * pWindow){
    SDL_Renderer * pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = NULL;
    font = TTF_OpenFont(FONT_PATH, 40); // Charger la police avec une taille de 24 points
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
    SDL_Color color = {255, 255, 255}; // Couleur blanche
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstRect = {x, y, texW, texH};
    SDL_RenderCopy(pRenderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(pRenderer);
    TTF_CloseFont(font);
}

int anim(int argc, char** argv, int lab[N][M], int niveau, character_t ** player){

/* ----------------------------------------------------- Initialisations ----------------------------------------------------- */

	int i = 0, j = 0, k = 0, quit = 0, pv1 = 1, pv2 = 4, pv3 = 7, pv4 = 10, j1 = 0, l1 = 0, p1 = 0; // Initialisation des compteurs pour les boucles d'animation
    int x = 0, y = 0, w = 0 , h = 0; // Initialisation des coordonnées communes à chaque animation
    int lastKeyPressed = -1; // Variable de la dernière touche préssée
    int saut = 0, gauche = 0, droite = 0, glissade = 0;
    int lkpshift; // Vaut 1 si la dernière combinaison comprenait shift (donc un drift)
    int lkpdash; // Vaut 1 si la dernière combinaison comprenait espace (donc un dash)
    int lastDirection = 1; // Vaut 1 ou 2 selon la dernière direction
    int timestamp, timestampnew;
    clock_gettime(CLOCK_REALTIME, &timestamp);

/* ----------------------------------------------------- Spawn aléatoire des entités ----------------------------------------------------- */

    character_t * jani1;
    create(&jani1, 50);
    creer_coord(&jani1, lab);

    character_t * pot1;
    create(&pot1, 50);
    creer_coord(&pot1, lab);
    
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
                SDL_Texture* pTexturePv = loadTexture("../sprites/fov/pv.png", pRenderer);
                SDL_Texture* pTextureJanitor = loadTexture("../sprites/npc/janitor_walk.png", pRenderer);
                SDL_Texture* pTextureLighter = loadTexture("../sprites/items/lighter.png", pRenderer);
                SDL_Texture* pTexturePotion = loadTexture("../sprites/items/potion.png", pRenderer);


                /*const char * regles = "Bienvenue à toi ! Ton but est d'arriver à la fin du labyrinthe, en bas à droite, tout en combattant
                les monstres grâce aux glissades/drifts!\n Tu disposes de plusieurs vies et si tu en perds tu peux régénérer avec des
                potions de vie et des morceaux de viande !\n BONNE CHANCE !";
                message_joueur(regles, (LONGUEUR * FORMATPIXELZOOM + FORMATPIXELZOOM) - 2 * FORMATPIXELZOOM,
                (LARGEUR * FORMATPIXELZOOM + FORMATPIXELZOOM) - 3 * FORMATPIXELZOOM,
                pWindow);*/




                //fonction d'affichage des animations des sprites
                if ( pTextureRun != NULL && pTextureDrift != NULL && pTextureDash != NULL && pTexturePv != NULL){
                        SDL_Rect position = {FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM};
			            SDL_Rect pvpos = {0, 0, 256, 256};
                        SDL_Rect jani1pos = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM};
                        SDL_Rect pot1pos = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM};
                        SDL_Rect lighterpos = {0, 0, FORMATPIXEL * ZOOM, FORMATPIXEL * ZOOM};
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
                        
			            /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de barre de vie*/

                        SDL_Rect hpbar[13] = {0, 0, 256, 256};
                        for (i=0;i<13;i++){
                            hpbar[i].x=x;
                            hpbar[i].y=0;
                            hpbar[i].w=256;
                            hpbar[i].h=256;
                            x+=256;
                        }
                        x=0;

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/
                        SDL_Rect janitor[10] = {0, 0, 256, 256};
                        for (j1=0;j1<10;j1++){
                            janitor[j1].x=x;
                            janitor[j1].y=0;
                            janitor[j1].w=FORMATPIXEL;
                            janitor[j1].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/
                        SDL_Rect lighter[15] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                        for (l1=0;l1<15;l1++){
                            lighter[l1].x=x;
                            lighter[l1].y=0;
                            lighter[l1].w=FORMATPIXEL;
                            lighter[l1].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/
                        SDL_Rect potion[16] = {0, 0, FORMATPIXEL/2, FORMATPIXEL/2};
                        for (p1=0;p1<16;p1++){
                            potion[p1].x=x;
                            potion[p1].y=0;
                            potion[p1].w=FORMATPIXEL;
                            potion[p1].h=FORMATPIXEL;
                            x+=FORMATPIXEL;
                        }
                        x=0;
                        
                        SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position); //copie du personnage dans sa position de base
                        SDL_RenderPresent(pRenderer); // Affichage
                        
                        // declaration de event pour récuperer les evenement
                        SDL_Event event;
                        SDL_Event event2;
                        
                        //declaration de quit etant la variable booleen qui met fin a la boucle
                        //declaration keyPressed pour gérer si une touche est maintenu ou relacher
                        int KeyIsPressed=0;
                        
                        //boucle du jeu

/* ----------------------------------------------------- Détection des frappes ----------------------------------------------------- */

                        int coefX = 0, coefY = 0;

                        while (!quit){
                            jani1pos.x = (((jani1->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                            jani1pos.y = (((jani1->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                            printf("%d, %d", jani1->x,jani1->y);
                            pot1pos.x = (((pot1->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                            pot1pos.y = (((pot1->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                            printf("%d, %d", pot1->x,pot1->y);
                            lighterpos.x = (((M) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                            lighterpos.y = (((N-1) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                            printf("Coordonées briquet : %d %d\n", lighterpos.x, lighterpos.y);
                            printf("Coordonées janitor : %d %d\n", jani1pos.x, jani1pos.y);
                            /*printf("Total :\nx = %d\t\ty = %d\nPrécis droit :\nx = %d y = %d\nPrécis gauche :\nx = %d y = %d\ncollisions :\nx = %d y = %d\n", 
                            position.x, position.y,
                            position.x % FORMATPIXELZOOM, position.y % FORMATPIXELZOOM);   //gauche*/
                            //printf("coefX : %d\tcoefY : %d\n", coefX, coefY);
                            printf("xglobal : %d\tyglobal : %d\n", position.x + 8, position.y);
                            printf("x = %d\ty = %d\n", ((position.x + 8) / FORMATPIXELZOOM / 9) + coefX, (position.y / FORMATPIXELZOOM / 9) + coefY);
                            //printf("x = %d et y = %d\n\n", position.x % FORMATPIXELZOOM, position.y % FORMATPIXELZOOM);
                            if(position.x >= 970 && coefX < M){
                                coefX += 10;
                                position.x = 16;
                            }
                            if(position.x <= 10 && coefX < M && coefX > 0){
                                coefX -= 10;
                                position.x = 960;
                            }
                            if(position.y >= 670 && coefY < N){
                                coefY += 7;
                                position.y = 2;
                            }
                            if(position.y <= 1 && coefY < N && coefY > 0){
                                coefY -= 7;
                                position.y = 660;
                            }
                            SDL_RenderClear(pRenderer);

                            //fin du niveau ?
                            if(((position.y / FORMATPIXELZOOM / 9) + coefY - 1 == N - 2 && ((position.x + 8) / FORMATPIXELZOOM / 9) - 1 + coefX == M - 1)
                        && lastDirection == 1
                            || ((position.y / FORMATPIXELZOOM / 9) + coefY - 1 == N - 2 && ((position.x + 70) / FORMATPIXELZOOM / 9) - 1 + coefX == M - 1 )
                        && lastDirection == 2){
                                position.x = FORMATPIXELZOOM, position.y = FORMATPIXELZOOM, coefX = 0, coefY = 0;
                                SDL_Delay(2000);
                                quit = 1;
                            }
                            if(niveau == 1)
                                affichage_laby_niveau_un(lab, pRenderer, coefX, coefY);
                            else if(niveau == 2)
                                affichage_laby_niveau_deux(lab, pRenderer, coefX, coefY);
                            else if(niveau == 3)
                                affichage_laby_niveau_trois(lab, pRenderer, coefX, coefY);
                            // récuperation du clic sur le bouton de fermeture et met fin a la boucle
                            while (SDL_PollEvent(&event)){
                                if (event.type == SDL_QUIT){
                                    quit = 2;
                                }

                                // Récuperation des frappes
                                if (event.type == SDL_KEYDOWN) {
                                    
                                    /*------------------------------ Run -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_d) {
                                        droite = 1;
                                        lastKeyPressed = 1;
                                    }
                                    if (event.key.keysym.sym == SDLK_q) {
                                        gauche = 1; 
                                        lastKeyPressed = 2;
                                    }

                                    /*------------------------------ Drift -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_LSHIFT){
                                        glissade = 1;
                                    }

                                    /*------------------------------ Dash -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_SPACE){
                                        saut = 1;
                                    }
                                }
                                
                                // Récuperation des touche relachées
                                else if (event.type == SDL_KEYUP) {
                                    if (event.key.keysym.sym == SDLK_q){
                                        gauche = 0;
                                        lastKeyPressed = -2;
                                    }
                                    if(event.key.keysym.sym == SDLK_d){
                                        droite = 0;
                                        lastKeyPressed = -1;
                                    }
                                    if(event.key.keysym.sym == SDLK_LSHIFT){
                                        glissade = 0;
                                    }
                                    if(event.key.keysym.sym == SDLK_SPACE){
                                        saut = 0;
                                    }

                                }
                            }

/* ----------------------------------------------------- Animation ----------------------------------------------------- */
                            /*------------------------------ Run -------------------------------*/

                            // Affichage run à droite (/ 9 = zoom²)
                            int gravite = 0;
                            if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][((position.x + 16) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT
                            && (lastKeyPressed == 1 || lastKeyPressed == -1)
                            || lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][((position.x + 80) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT 
                            && (lastKeyPressed == 2 || lastKeyPressed == -2))
                                gravite = 1;



                            if(position.x < FORMATPIXELZOOM - 32 && coefX == 0){
                                position.x = FORMATPIXELZOOM - 8;
                                SDL_Delay(50);
                            }

                            if(position.x > (M * FORMATPIXELZOOM) - 22 && coefX == 50){
                                position.x = (M * FORMATPIXELZOOM) - 32;
                                SDL_Delay(50);
                            }

                            if(position.y < FORMATPIXELZOOM && coefY == 0){
                                position.y = FORMATPIXELZOOM;
                                SDL_Delay(15);
                            }

                            if(gravite){
                                position.y += 2 * ZOOM;
                                SDL_Delay(10);
                            }
                            


                            //run droite
                            if(droite && !gauche && !glissade && !saut){
                                if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][(position.x / FORMATPIXELZOOM / 9) + coefX] != DUR
                                && (position.x + 8) % FORMATPIXELZOOM <= 72){
                                    position.x += 1 * ZOOM;
                                    SDL_Delay(4);
                                }
                                SDL_RenderCopy(pRenderer,pTextureRun,run+((++i)%11),&position);
                            }

                            // Affichage run à gauche
                            else if(gauche && !droite && !saut && !glissade){
                                if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][((position.x) / FORMATPIXELZOOM / 9) - 1 + coefX] != DUR
                                && position.x % FORMATPIXELZOOM >= 24){
                                    position.x-=1 * ZOOM;
                                    SDL_Delay(4);
                                }
                                SDL_RenderCopyEx(pRenderer,pTextureRun,run+((++i)%11),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                            }

                            /*------------------------------ Statique -------------------------------*/

                            // Affichage statique gauche
                            else if(!saut && !gauche && !droite && !glissade && lastKeyPressed == 1){
                                SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position);
                            }

                            
                            // Affichage statique droite
                            else if(!saut && !gauche && !droite && !glissade && lastKeyPressed == 2){
                                SDL_RenderCopyEx(pRenderer,pTextureRun,run+0,&position, 0, NULL, SDL_FLIP_HORIZONTAL);// Affichage statique
                            }

                            /*------------------------------ Drift -------------------------------*/

                            // Affichage drift gauche
                            else if(glissade && gauche && !droite && !saut){
                                position.x -= 6 * ZOOM;
                                SDL_Delay(8);
                                if(j == 23){
                                    SDL_RenderCopyEx(pRenderer,pTextureDrift,drift+((23)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }else{
                                    SDL_RenderCopyEx(pRenderer,pTextureDrift,drift+((++j)),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                }
                            }

                            // Affichage drift droite
                            else if(glissade && !gauche && droite && !saut){
                                position.x += 6 * ZOOM;
                                SDL_Delay(8);
                                if(j == 23){
                                    SDL_RenderCopy(pRenderer,pTextureDrift,drift+((23)),&position);
                                }else{
                                    SDL_RenderCopy(pRenderer,pTextureDrift,drift+((++j)),&position);
                                }
                            }

                            /*------------------------------ Dash -------------------------------*/

                            // Affichage dash droite
                            else if(saut && droite && !gauche && !glissade){
                                printf("\nSAUT DROITE\n");
                                if(lab[(position.y / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 8) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT)
                                {
                                    position.x += 2 * ZOOM;
                                    position.y -= 3 * ZOOM;
                                    SDL_Delay(8);
                                }
                                SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)%20),&position);
                            }

                            // Affichage dash gauche
                           else if(saut && !droite && gauche && !glissade){
                                printf("\nSAUT GAUCHE\n");
                                if(lab[(position.y / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 70) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                                    position.x -= 2 * ZOOM;
                                    position.y -= 3 * ZOOM;
                                    SDL_Delay(8);
                                }
                                SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)%20),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                            }

                            // Affichage dash statique à droite
                            else if(saut && !droite && !gauche && !glissade && lastKeyPressed == -1){
                                printf("\nSAUT STAT DROITE\n");
                                if(lab[((position.y) / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 8) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                                    position.y -= 4 * ZOOM;
                                    SDL_Delay(8);
                                }
                                SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k)%20),&position);
                            }

                            // Affichage dash statique à gauche
                            else if(saut && !gauche && !droite && !glissade && lastKeyPressed == -2){
                                printf("\nSAUT STAT GAUCHE\n");
                                if(lab[((position.y) / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 70) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                                    position.y -= 4 *  ZOOM;
                                    SDL_Delay(8);
                                }
                                SDL_RenderCopyEx(pRenderer,pTextureDash,dash+((++k)%20),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                            }
                        
                            
                            /*------------------------------ Default -------------------------------*/
 
                            else{
                                if(lastKeyPressed == -1){
                                    SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position);
                                     // Affichage défaut   
                                }else{
                                    SDL_RenderCopyEx(pRenderer,pTextureRun,run+0,&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                                // Affichage défaut   
                                }
                                
                            }

			                if((*player)->pv > 80){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+0,&pvpos); // anima stop coeur 4
                            }
                            else if((*player)->pv <= 80 && (*player)->pv >= 70){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+pv1,&pvpos); // anima continue coeur 4∕3
                                if(pv1 == 1){
                                    pv1 = 2;
                                }else{
                                    pv1 = 1;
                                }
                            }
                            else if((*player)->pv < 70 && (*player)->pv > 55){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+3,&pvpos); // anima stop coeur 3
                            }
                            else if((*player)->pv <= 55 && (*player)->pv >= 45){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+pv2,&pvpos); // anima continue coeur 3/2
                                if(pv2 == 4){
                                    pv2 = 5;
                                }else{
                                    pv2 = 4;
                                }
                            }
                            else if((*player)->pv < 45 && (*player)->pv > 30){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+6,&pvpos); // anima stop coeur 2
                            }
                            else if((*player)->pv <= 30 && (*player)->pv >= 20){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+pv3,&pvpos); // anima continue coeur 2/1
                                if(pv3 == 7){
                                    pv3 = 8;
                                }else{
                                    pv3 = 7;
                                }
                            }
                            else if((*player)->pv < 20 && (*player)->pv > 5){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+9,&pvpos); // anima stop coeur 1
                            }
                            else if((*player)->pv <= 5 && (*player)->pv >= 0){
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+pv4,&pvpos); // anima continue coeur 1/0
                                if(pv4 == 10){
                                    pv4 = 11;
                                }else{
                                    pv4 = 10;
                                }
                            }
                            else{
                                SDL_RenderCopy(pRenderer,pTexturePv,hpbar+12,&pvpos); // anima stop coeur 0
                            }

                            SDL_RenderCopy(pRenderer,pTextureJanitor,janitor+((j1++)%10),&jani1pos); // anim janitor

                            if(abs((position.x / FORMATPIXELZOOM / 9) - (jani1pos.x / FORMATPIXELZOOM / 9)) < 2 && abs((position.y / FORMATPIXELZOOM / 9) - (jani1pos.y / FORMATPIXELZOOM / 9)) < 2){
                                clock_gettime(CLOCK_REALTIME, &timestampnew);
                                if(timestampnew - timestamp > 1){
                                    attack(player, &jani1);
                                    clock_gettime(CLOCK_REALTIME, &timestamp);
                                }
                            }

                            SDL_RenderCopy(pRenderer,pTexturePotion,potion+((p1++)%16),&pot1pos); // anim potion
                            printf("Coordonées aprè jani1pos : %d, %d\n\n", jani1->x, jani1->y);
                            if(niveau == 1){
                                printf("je suis la");
                                SDL_RenderCopy(pRenderer,pTextureLighter,lighter+((l1++)%15), &lighterpos); // anim lighter
                            }
                            // Délai générique à toutes les animations
                            SDL_RenderPresent(pRenderer); // Affichage du Renderer
                        }

                        

                        

/* ----------------------------------------------------- Libération de la mémoire des textures ----------------------------------------------------- */

                        SDL_DestroyTexture(pTextureRun);
                        SDL_DestroyTexture(pTextureDrift);
                        SDL_DestroyTexture(pTextureDash);
                        SDL_DestroyTexture(pTexturePv);
                    
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
    return quit;
}
