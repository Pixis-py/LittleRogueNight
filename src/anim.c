/**
 * @file anim.c
 * @author Clément Lelandais, Maelig Pesantez, Enzo Desfaudais
 * @brief Main game file used to manage Six's animations, therefore movements, collisions and also entity management.
 * @version 0.1
 * @date 2024-04-24
 * @copyright Copyright (c) 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lib/anim.h"

/**
 * @brief Generate valid coordonates randomly and assign them to the entity
 * 
 * @param ent 
 * @param lab 
 */

void creer_coord(character_t ** ent, int lab[N][M]){
    int x, y, i, j, possible = 0;
    while(!possible){
        x = rand() % N;
        y = rand() % M;
            if(lab[x][y] == NUIT && lab[x + 1][y] == TERREVERTE)
                possible = 1;
    }
    (*ent)->x = y + 1;
    (*ent)->y = x + 1;
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @param lab 
 * @param niveau 
 * @param player 
 * @return int 
 */
int anim(int argc, char** argv, int lab[N][M], int niveau, character_t ** player){
/* ----------------------------------------------------- Initialisations ----------------------------------------------------- */

    //declaration de quit etant la variable booleen qui met fin a la boucle
    int i = 0, j = 0, k = 0, quit = 0, pv1 = 1, pv2 = 4, pv3 = 7, pv4 = 10, j1 = 0, l1 = 0, p1 = 0, m1 = 0; // Initialisation des compteurs pour les boucles d'animation
    int x = 0, y = 0, w = 0 , h = 0; // Initialisation des coordonnées communes à chaque animation
    int lastKeyPressed = -1; // Variable de la dernière touche préssée
    int saut = 0, gauche = 0, droite = 0, glissade = 0;
    int lkpshift; // Vaut 1 si la dernière combinaison comprenait shift (donc un drift)
    int lkpdash; // Vaut 1 si la dernière combinaison comprenait espace (donc un dash)
    int lastDirection = 1; // Vaut 1 ou 2 selon la dernière direction
    int retirer_pot = 0, retirer_pot2 = 0, retirer_pot3 = 0, retirer_pot4 = 0;
    int retirer_meat = 0, retirer_meat2 = 0, retirer_meat3 = 0, retirer_meat4 = 0;
    struct timespec timestamp, timestampnew;
    clock_gettime(CLOCK_REALTIME, &timestamp);
/* ----------------------------------------------------- Spawn aléatoire des entités ----------------------------------------------------- */

    character_t * jani;
    character_t * jani2;
    character_t * jani3;
    character_t * jani4;
    character_t * jani5;

    if(niveau == 1){
        create(&jani, 50, 15);
        create(&jani2, 50, 15);
        create(&jani3, 50, 15);
        create(&jani4, 50, 15);
        create(&jani5, 50, 15);
    }

    else if(niveau == 2){
        create(&jani, 50, 20);
        create(&jani2, 50, 20);
        create(&jani3, 50, 20);
        create(&jani4, 50, 20);
        create(&jani5, 50, 20);
    }

    else if(niveau == 3){
        create(&jani, 50, 30);
        create(&jani2, 50, 30);
        create(&jani3, 50, 30);
        create(&jani4, 50, 30);
        create(&jani5, 50, 30);
    }

    creer_coord(&jani, lab);
    creer_coord(&jani2, lab);
    creer_coord(&jani3, lab);
    creer_coord(&jani4, lab);
    creer_coord(&jani5, lab);

    character_t * pot;
    character_t * pot2;
    character_t * pot3;
    character_t * pot4;

    create(&pot, 25, 0);
    create(&pot2, 25, 0);
    create(&pot3, 25, 0);
    create(&pot4, 25, 0);

    creer_coord(&pot, lab);
    creer_coord(&pot2, lab);
    creer_coord(&pot3, lab);
    creer_coord(&pot4, lab);

    character_t * meat;
    character_t * meat2;
    character_t * meat3;
    character_t * meat4;

    create(&meat, 20, 0);
    create(&meat2, 20, 0);
    create(&meat3, 20, 0);
    create(&meat4, 20, 0);

    creer_coord(&meat, lab);
    creer_coord(&meat2, lab);
    creer_coord(&meat3, lab);
    creer_coord(&meat4, lab);

/* ----------------------------------------------------- Création et gestion de la fenêtre SDL ----------------------------------------------------- */

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0){
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
        if(pWindow){
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
                SDL_Texture* pTextureMeat = loadTexture("../sprites/items/meat.png", pRenderer);

            //fonction d'affichage des animations des sprites

            if ( pTextureRun != NULL && pTextureDrift != NULL && pTextureDash != NULL && pTexturePv != NULL){

                SDL_Rect position = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect pvpos = {0, 0, 256, 256};
                SDL_Rect janipos = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};                 
                SDL_Rect janipos2 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect janipos3 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect janipos4 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect janipos5 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};

                SDL_Rect potpos = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect potpos2 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect potpos3 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect potpos4 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};

                SDL_Rect meatpos = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect meatpos2 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect meatpos3 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};
                SDL_Rect meatpos4 = {FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM, FORMATPIXELZOOM};

                SDL_Rect lighterpos = {0, 0, FORMATPIXELZOOM, FORMATPIXELZOOM};

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de marche*/

                SDL_Rect run[11] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                for (i = 0; i < 11; i++){
                    run[i].x =x;
                    run[i].y = 0;
                    run[i].w = FORMATPIXEL;
                    run[i].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de drift*/

                SDL_Rect drift[24] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                for (j = 0; j < 24; j++){
                    drift[j].x = x;
                    drift[j].y = 0;
                    drift[j].w = FORMATPIXEL;
                    drift[j].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }  
                x = 0;
                j=-1;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de dash*/

                SDL_Rect dash[20] = { 0,0, FORMATPIXEL,FORMATPIXEL};
                for (k = 0; k < 20; k++){
                    dash[k].x = x;
                    dash[k].y = 0;
                    dash[k].w = FORMATPIXEL;
                    dash[k].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;
                k = -1; 

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de barre de vie*/

                SDL_Rect hpbar[13] = {0, 0, 256, 256};
                for (i = 0; i < 13; i++){
                    hpbar[i].x = x;
                    hpbar[i].y = 0;
                    hpbar[i].w = 256;
                    hpbar[i].h = 256;
                    x += 256;
                }
                x = 0;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/

                SDL_Rect janitor[10] = {0, 0, 256, 256};
                for (j1 = 0; j1 < 10; j1++){
                    janitor[j1].x = x;
                    janitor[j1].y = 0;
                    janitor[j1].w = FORMATPIXEL;
                    janitor[j1].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/

                SDL_Rect lighter[15] = {0, 0, FORMATPIXEL, FORMATPIXEL};
                for (l1 = 0; l1 < 15; l1++){
                    lighter[l1].x = x;
                    lighter[l1].y = 0;
                    lighter[l1].w = FORMATPIXEL;
                    lighter[l1].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/

                SDL_Rect potion[16] = {0, 0, FORMATPIXEL / 2, FORMATPIXEL / 2};
                for (p1 = 0; p1 < 16; p1++){
                    potion[p1].x = x;
                    potion[p1].y = 0;
                    potion[p1].w = FORMATPIXEL;
                    potion[p1].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;

                /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation d'un janitor(monstre)'*/
                
                SDL_Rect viande[11] = {0, 0, FORMATPIXEL / 2, FORMATPIXEL / 2};
                for (m1 = 0; m1 < 11; m1++){
                    viande[m1].x = x;
                    viande[m1].y = 0;
                    viande[m1].w = FORMATPIXEL;
                    viande[m1].h = FORMATPIXEL;
                    x += FORMATPIXEL;
                }
                x = 0;

                SDL_RenderCopy(pRenderer,pTextureRun,run+0,&position); //copie du personnage dans sa position de base
                SDL_RenderPresent(pRenderer); // Affichage
                // déclaration de event pour récuperer les evenements

                SDL_Event event;
                //declaration keyPressed pour gérer si une touche est maintenue ou relachée
                int KeyIsPressed = 0;

                //boucle du jeu
                /* ----------------------------------------------------- Détection des frappes ----------------------------------------------------- */
                int coefX = 0, coefY = 0;
                while (!quit){
                    janipos.x = (((jani->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    janipos.y = (((jani->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    janipos2.x = (((jani2->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    janipos2.y = (((jani2->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    janipos3.x = (((jani3->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    janipos3.y = (((jani3->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    janipos4.x = (((jani4->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    janipos4.y = (((jani4->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    janipos5.x = (((jani5->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    janipos5.y = (((jani5->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);

                    potpos.x = (((pot->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    potpos.y = (((pot->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    potpos2.x = (((pot2->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    potpos2.y = (((pot2->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    potpos3.x = (((pot3->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    potpos3.y = (((pot3->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    potpos4.x = (((pot4->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    potpos4.y = (((pot4->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);

                    meatpos.y = (((meat->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    meatpos.x = (((meat->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    meatpos2.x = (((meat2->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    meatpos2.y = (((meat2->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    meatpos3.x = (((meat3->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    meatpos3.y = (((meat3->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);
                    meatpos4.x = (((meat4->x) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    meatpos4.y = (((meat4->y) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);

                    lighterpos.x = (((M) * FORMATPIXELZOOM) - coefX * FORMATPIXELZOOM);
                    lighterpos.y = (((N - 1) * FORMATPIXELZOOM) - coefY * FORMATPIXELZOOM);

                    //Test décalage de Six sur les bordures de l'écran
                    if(position.x >= 970 && coefX < M){
                        coefX += LONGUEUR;
                        position.x = 16;
                    }
                    if(position.x <= 10 && coefX < M && coefX > 0){
                        coefX -= LONGUEUR;
                        position.x = 960;
                    }
                    if(position.y >= 670 && coefY < N){
                        coefY += LARGEUR;
                        position.y = 2;
                    }
                    if(position.y <= 1 && coefY < N && coefY > 0){
                        coefY -= LARGEUR;
                        position.y = 660;
                    }
                    SDL_RenderClear(pRenderer);

                    //fin du niveau ?
                    if(((position.y / FORMATPIXELZOOM / 9) + coefY - 1 == N - 2 && 
                    ((position.x + 8) / FORMATPIXELZOOM / 9) - 1 + coefX == M - 1)
                    && lastDirection == 1

                    || 
                    
                    ((position.y / FORMATPIXELZOOM / 9) + coefY - 1 == N - 2 &&
                    ((position.x + 70) / FORMATPIXELZOOM / 9) - 1 + coefX == M - 1 )
                    && lastDirection == 2){
                        position.x = FORMATPIXELZOOM, position.y = FORMATPIXELZOOM, coefX = 0, coefY = 0;
                        SDL_Delay(1500);
                        quit = 1;
                    }
                    //Six meurt ?
                    if((*player)->pv == 0){
                        position.x = FORMATPIXELZOOM, position.y = FORMATPIXELZOOM, coefX = 0, coefY = 0;
                        niveau = 1;
                        creer_coord(&pot, lab);
                        creer_coord(&pot2, lab);
                        creer_coord(&pot3, lab);
                        creer_coord(&pot4, lab);
                        creer_coord(&meat, lab);
                        creer_coord(&meat2, lab);
                        creer_coord(&meat3, lab);
                        creer_coord(&meat4, lab);
                        creer_coord(&jani, lab);
                        creer_coord(&jani2, lab);
                        creer_coord(&jani3, lab);
                        creer_coord(&jani4, lab);
                        creer_coord(&jani5, lab);
                        pv_gain(&jani, 50 - jani->pv);
                        pv_gain(&jani2, 50 - jani2->pv);
                        pv_gain(&jani3, 50 - jani3->pv);
                        pv_gain(&jani4, 50 - jani4->pv);
                        pv_gain(&jani5, 50 - jani5->pv);
                        pv_gain(player, 100);
                    }

                    if(niveau == 1)
                        affichage_laby_niveau_un(lab, pRenderer, coefX, coefY);
                    else if(niveau == 2)
                        affichage_laby_niveau_deux(lab, pRenderer, coefX, coefY);
                    else if(niveau == 3)
                        affichage_laby_niveau_trois(lab, pRenderer, coefX, coefY);
                    
                    // récuperation du clic sur le bouton de fermeture et met fin a la boucle

                    while (SDL_PollEvent(&event)){

                        if (event.type == SDL_QUIT)
                            quit = 2;
                        
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
                            if (event.key.keysym.sym == SDLK_LSHIFT)
                                glissade = 1;
                        
                            /*------------------------------ Dash -------------------------------*/

                            if (event.key.keysym.sym == SDLK_SPACE)
                                saut = 1;
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

                            if(event.key.keysym.sym == SDLK_LSHIFT)
                                glissade = 0;

                            if(event.key.keysym.sym == SDLK_SPACE)
                                saut = 0;
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

                    if(position.x < FORMATPIXELZOOM - FORMATPIXEL && coefX == 0){
                        position.x = FORMATPIXELZOOM - 8;
                        SDL_Delay(50);
                    }

                    if(position.x > (M * FORMATPIXELZOOM) - 22 && coefX == 50){
                        position.x = (M * FORMATPIXELZOOM) - FORMATPIXEL;
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

                    //Affichage run à droite
                    if(droite && !gauche && !glissade && !saut){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][(position.x / FORMATPIXELZOOM / 9) + coefX] != DUR
                        && (position.x + 8) % FORMATPIXELZOOM <= 72){
                            position.x += 1 * ZOOM;
                            SDL_Delay(4);
                        }
                        SDL_RenderCopy(pRenderer,pTextureRun,run+((++i) % 11),&position);
                    }

                    // Affichage run à gauche
                    else if(gauche && !droite && !saut && !glissade){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][((position.x) / FORMATPIXELZOOM / 9) - 1 + coefX] != DUR
                        && position.x % FORMATPIXELZOOM >= 24){
                            position.x -= 1 * ZOOM;
                            SDL_Delay(4);
                        }
                        SDL_RenderCopyEx(pRenderer,pTextureRun,run+((++i) % 11),&position, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }

                    /*------------------------------ Statique -------------------------------*/

                    // Affichage statique gauche
                    else if(!saut && !gauche && !droite && !glissade && lastKeyPressed == 1)
                        SDL_RenderCopy(pRenderer, pTextureRun, run + 0, &position);
                    
                    // Affichage statique droite
                    else if(!saut && !gauche && !droite && !glissade && lastKeyPressed == 2)
                        SDL_RenderCopyEx(pRenderer, pTextureRun, run + 0, &position, 0, NULL, SDL_FLIP_HORIZONTAL);

                    /*------------------------------ Drift -------------------------------*/

                    // Affichage drift gauche
                    else if(glissade && gauche && !droite && !saut){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][((position.x) / FORMATPIXELZOOM / 9) - 1 + coefX] != DUR
                        && position.x % FORMATPIXELZOOM >= 32){
                            position.x -= 2 * ZOOM;
                            SDL_Delay(8);
                        }
                        if(j == 23)
                            SDL_RenderCopyEx(pRenderer, pTextureDrift, drift + ((23)), &position, 0, NULL, SDL_FLIP_HORIZONTAL);
                        else
                            SDL_RenderCopyEx(pRenderer, pTextureDrift, drift + ((++j)), &position, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }

                    // Affichage drift droite
                    else if(glissade && !gauche && droite && !saut){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) + coefY][(position.x / FORMATPIXELZOOM / 9) + coefX] != DUR
                        && (position.x + 8) % FORMATPIXELZOOM <= 64){
                            position.x += 2 * ZOOM;
                            SDL_Delay(8);
                        }
                        if(j == 23)
                            SDL_RenderCopy(pRenderer, pTextureDrift, drift + ((23)), &position);
                        else
                            SDL_RenderCopy(pRenderer, pTextureDrift, drift + ((++j)), &position);
                    }

                    /*------------------------------ Dash -------------------------------*/
                    // Affichage dash droite
                    else if(saut && droite && !gauche && !glissade){
                        if(lab[(position.y / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x - 24)/ FORMATPIXELZOOM / 9) + coefX] == NUIT)
                        {
                            position.x += 2 * ZOOM;
                            position.y -= 4 * ZOOM;
                            SDL_Delay(8);
                        }
                        SDL_RenderCopy(pRenderer,pTextureDash,dash+((++k) % 20), &position);
                    }

                    // Affichage dash gauche
                    else if(saut && !droite && gauche && !glissade){
                        if(lab[(position.y / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 24) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                            position.x -= 2 * ZOOM;
                            position.y -= 4 * ZOOM;
                            SDL_Delay(8);
                        }
                        SDL_RenderCopyEx(pRenderer, pTextureDash, dash + ((++k) % 20), &position, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }

                    // Affichage dash statique à droite
                    else if(saut && !droite && !gauche && !glissade && lastKeyPressed == -1){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 8) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                            position.y -= 4 * ZOOM;
                            SDL_Delay(8);
                        }
                        SDL_RenderCopy(pRenderer, pTextureDash, dash + ((++k) % 20), &position);
                    }

                    // Affichage dash statique à gauch
                    else if(saut && !gauche && !droite && !glissade && lastKeyPressed == -2){
                        if(lab[((position.y) / FORMATPIXELZOOM / 9) - 1 + coefY][((position.x + 70) / FORMATPIXELZOOM / 9) - 1 + coefX] == NUIT){
                            position.y -= 4 * ZOOM;
                            SDL_Delay(8);
                        }
                        SDL_RenderCopyEx(pRenderer, pTextureDash, dash + ((++k) % 20), &position, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }

                    /*------------------------------ Default -------------------------------*/

                    else{
                        if(lastKeyPressed == -1)
                            SDL_RenderCopy(pRenderer, pTextureRun, run + 0, &position);
                        else
                            SDL_RenderCopyEx(pRenderer, pTextureRun, run + 0, &position, 0, NULL, SDL_FLIP_HORIZONTAL);
                    }

                    if((*player)->pv > 80)
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + 0, &pvpos); // anima stop coeur 4
                    else if((*player)->pv <= 80 && (*player)->pv >= 70){
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + pv1, &pvpos); // anima continue coeur 4∕3
                        if(pv1 == 1)
                            pv1 = 2;
                        else
                            pv1 = 1;
                    }
                    else if((*player)->pv < 70 && (*player)->pv > 55)
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + 3, &pvpos); // anima stop coeur 3
                    else if((*player)->pv <= 55 && (*player)->pv >= 45){
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar +pv2, &pvpos); // anima continue coeur 3/2
                        if(pv2 == 4)
                            pv2 = 5;
                        else
                            pv2 = 4;
                    }
                    else if((*player)->pv < 45 && (*player)->pv > 30)
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + 6, &pvpos); // anima stop coeur 2
                    else if((*player)->pv <= 30 && (*player)->pv >= 20){
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + pv3, &pvpos); // anima continue coeur 2/1
                        if(pv3 == 7)
                            pv3 = 8;
                        else
                            pv3 = 7;
                    }
                    else if((*player)->pv < 20 && (*player)->pv > 5)
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + 9, &pvpos); // anima stop coeur 1
                    else if((*player)->pv <= 5 && (*player)->pv >= 0){
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + pv4, &pvpos); // anima continue coeur 1/0
                        if(pv4 == 10)
                            pv4 = 11;
                        else
                            pv4 = 10;
                    }
                    else{
                        SDL_RenderCopy(pRenderer, pTexturePv, hpbar + 12, &pvpos); // anima stop coeur 0
                        SDL_Delay(20);
                    }

                    if(jani->pv > 0)
                        SDL_RenderCopy(pRenderer, pTextureJanitor, janitor + ((j1++) % 10), &janipos); // anim janitor
                    if(jani2->pv > 0)
                        SDL_RenderCopy(pRenderer, pTextureJanitor, janitor + ((j1++) % 10), &janipos2); // anim janitor
                    if(jani3->pv > 0)
                        SDL_RenderCopy(pRenderer, pTextureJanitor, janitor + ((j1++) % 10), &janipos3); // anim janitor
                    if(jani4->pv > 0)
                        SDL_RenderCopy(pRenderer, pTextureJanitor, janitor + ((j1++) % 10), &janipos4); // anim janitor
                    if(jani5->pv > 0)
                    SDL_RenderCopy(pRenderer, pTextureJanitor, janitor + ((j1++) % 10), &janipos5); // anim janitor

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos.y / FORMATPIXELZOOM / 9)) == 0
                    && !glissade && jani->pv > 0){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        //Pour l'attque du monstre, il fait subir des dégâts toutes les 1.5 secondes
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1.5){
                            pv_loss(player, jani->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos.y / FORMATPIXELZOOM / 9)) == 0
                    && glissade && (droite || gauche)){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        //Pour l'attque de Six, il fait subir des dégâts toutes les 0.25 secondes
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.25){
                            pv_loss(&jani, (*player)->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos2.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos2.y / FORMATPIXELZOOM / 9)) == 0
                    && !glissade && jani2->pv > 0){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1.5){
                            pv_loss(player, jani2->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos2.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos2.y / FORMATPIXELZOOM / 9)) == 0
                    && glissade && (droite || gauche)){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.25){
                            pv_loss(&jani2, (*player)->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos3.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos3.y / FORMATPIXELZOOM / 9)) == 0
                    && !glissade && jani3->pv > 0){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1.5){
                            pv_loss(player, jani3->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos3.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos3.y / FORMATPIXELZOOM / 9)) == 0
                    && glissade && (droite || gauche)){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.25){
                            pv_loss(&jani3, (*player)->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos4.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos4.y / FORMATPIXELZOOM / 9)) == 0
                    && !glissade && jani4->pv > 0){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1.5){
                            pv_loss(player, jani4->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos4.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos4.y / FORMATPIXELZOOM / 9)) == 0
                    && glissade && (droite || gauche)){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.25){
                            pv_loss(&jani4, (*player)->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos5.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos5.y / FORMATPIXELZOOM / 9)) == 0
                    && !glissade && jani5->pv > 0){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1.5){
                            pv_loss(player, jani5->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (janipos5.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (janipos5.y / FORMATPIXELZOOM / 9)) == 0
                    && glissade && (droite || gauche)){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.25){
                            pv_loss(&jani5, (*player)->damage);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                        }
                    }



                    if(abs((position.x / FORMATPIXELZOOM / 9) - (potpos.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (potpos.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_pot && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        //Pour le gain de pv que procure une potion, il faut rester sur sa case pendant 1 seconde
                        if(timestampnew.tv_sec - timestamp.tv_sec > 1){
                            pv_gain(player, pot->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_pot = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (potpos2.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (potpos2.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_pot2 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, pot2->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_pot2 = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (potpos3.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (potpos3.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_pot3 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, pot3->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_pot3 = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (potpos4.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (potpos4.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_pot4 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, pot4->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_pot4 = 1;
                        }
                    }



                    if(abs((position.x / FORMATPIXELZOOM / 9) - (meatpos.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (meatpos.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_meat && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, meat->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_meat = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (meatpos2.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (meatpos2.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_meat2 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, meat2->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_meat2 = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (meatpos3.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (meatpos3.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_meat3 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, meat3->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_meat3 = 1;
                        }
                    }

                    if(abs((position.x / FORMATPIXELZOOM / 9) - (meatpos4.x / FORMATPIXELZOOM / 9)) < 2
                    && abs((position.y / FORMATPIXELZOOM / 9) - (meatpos4.y / FORMATPIXELZOOM / 9)) == 0
                    && !retirer_meat4 && (*player)->pv < 100){
                        clock_gettime(CLOCK_REALTIME, &timestampnew);
                        if(timestampnew.tv_sec - timestamp.tv_sec > 0.5){
                            pv_gain(player, meat4->pv);
                            clock_gettime(CLOCK_REALTIME, &timestamp);
                            retirer_meat4 = 1;
                        }
                    }

                    if(!retirer_pot)
                        SDL_RenderCopy(pRenderer, pTexturePotion, potion + ((p1++) % 16), &potpos); // anim potion
                    if(!retirer_pot2)
                        SDL_RenderCopy(pRenderer, pTexturePotion, potion + ((p1++) % 16), &potpos2); // anim potion
                    if(!retirer_pot3)
                        SDL_RenderCopy(pRenderer, pTexturePotion, potion + ((p1++) % 16), &potpos3); // anim potion
                    if(!retirer_pot4)
                        SDL_RenderCopy(pRenderer, pTexturePotion, potion + ((p1++) % 16), &potpos4); // anim potion

                    if(!retirer_meat)
                        SDL_RenderCopy(pRenderer, pTextureMeat, viande + ((m1++) % 11), &meatpos); // anim potion
                    if(!retirer_meat2)
                        SDL_RenderCopy(pRenderer, pTextureMeat, viande + ((m1++) % 11), &meatpos2); // anim potion
                    if(!retirer_meat3)
                        SDL_RenderCopy(pRenderer, pTextureMeat, viande + ((m1++) % 11), &meatpos3); // anim potion
                    if(!retirer_meat4)
                        SDL_RenderCopy(pRenderer, pTextureMeat, viande + ((m1++) % 11), &meatpos4); // anim potion

                    if(niveau == 1)
                        SDL_RenderCopy(pRenderer, pTextureLighter, lighter + ((l1++)%15), &lighterpos); // anim lighter

                    SDL_RenderPresent(pRenderer); // Affichage du Renderer
                }

        /* ----------------------------------------------------- Libération de la mémoire des textures ----------------------------------------------------- */

                SDL_DestroyTexture(pTextureRun);
                SDL_DestroyTexture(pTextureDrift);
                SDL_DestroyTexture(pTextureDash);
                SDL_DestroyTexture(pTexturePv);
                SDL_DestroyTexture(pTextureJanitor);
                SDL_DestroyTexture(pTextureLighter);
                SDL_DestroyTexture(pTexturePotion);
                SDL_DestroyTexture(pTextureMeat);
            }
            else
                fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
            SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
            }
            else
                fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());

            SDL_Delay(500); // Attente pour le chargement de la page
            SDL_DestroyWindow(pWindow); // Libération de la mémoire de la fenêtre SDL
        }
        else
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
    SDL_Quit();
    IMG_Quit();
    return quit;
}
