#include <stdio.h>
#include <SDL2/SDL.h>
#include "../lib/bouton.h"
#include "../lib/image.h"

/**
 * @file menu.c
 * @author Enzo Desfaudais
 * @brief menu.c is used to show the first menu and choose the character for the game
 * @version 1.0
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/// @brief menu is used to show the first menu and choose the character for the game
/// @param argc 
/// @param argv 
/// @param choix_perso 
/// @return the choice of the player to play the game or quit the game.
int menu(int argc, char** argv,int *choix_perso){

/* ----------------------------------------------------- Initialisation ----------------------------------------------------- */
    int play_result = 0;
    int opt_result = 0;
    int quit_result = 0;
    //declaration de quit la variable booleene qui met fin a la boucle
    int quit = 0;
    int quit_opt = 0;

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

                SDL_Texture* pTextureMenuWallpaper =loadTexture("../sprites/menu/menuWallpaper.png",pRenderer);
                SDL_Texture* pTexturePlayButton =loadTexture("../sprites/menu/play.png",pRenderer);
                SDL_Texture* pTexturePlayPressButton =loadTexture("../sprites/menu/play_hoover.png",pRenderer);
                SDL_Texture* pTextureOptionsButton =loadTexture("../sprites/menu/options.png",pRenderer);
                SDL_Texture* pTextureOptionsPressButton =loadTexture("../sprites/menu/options_hoover.png",pRenderer);
                SDL_Texture* pTextureQuitButton =loadTexture("../sprites/menu/quit.png",pRenderer);
                SDL_Texture* pTextureQuitPressButton =loadTexture("../sprites/menu/quit_hoover.png",pRenderer);
                SDL_Texture* pTexturePersoSix = loadTexture("../sprites/portraits/six_portrait.png",pRenderer);
                SDL_Texture* pTexturePersoMono = loadTexture("../sprites/portraits/mono_portrait.png",pRenderer);
                SDL_Texture* pTexturePersoSixHoover = loadTexture("../sprites/portraits/six_portrait_hover.png",pRenderer);
                SDL_Texture* pTexturePersoMonoHoover = loadTexture("../sprites/portraits/mono_portrait_hover.png",pRenderer);





                if ( pTextureMenuWallpaper != NULL){

                        SDL_Delay(500);
                        SDL_Rect menuWallpaper= {0,0, 1280, 720};
                        SDL_Rect playButton= {510, 310, 260, 100};
                        SDL_Rect optionsButton= {870, 310, 260, 100};
                        SDL_Rect quitButton= {150, 310, 260, 100};
                        SDL_Rect Choix_six={150, 100, 200, 500};
                        SDL_Rect Choix_mono={975,100,200,500};
                        SDL_Rect Opt_Quit = {510, 310, 260, 100};

                        SDL_Delay(500);


                        
                        //boucle du jeux

                        SDL_Event event;

/* ----------------------------------------------------- Détection des frappes ----------------------------------------------------- */

                        while (!quit) {
                            SDL_RenderClear(pRenderer);

/* ----------------------------------------------------- Animation ----------------------------------------------------- */
                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    quit = 1;
                                }
                            }

                            SDL_RenderCopy(pRenderer,pTextureMenuWallpaper, NULL, &menuWallpaper);
                            if(aff_bout(pRenderer,&playButton, event,pTexturePlayPressButton,pTexturePlayButton)){
                                play_result=1;
                                quit = 1;
                            }
                            if (aff_bout(pRenderer,&optionsButton,event,pTextureOptionsPressButton,pTextureOptionsButton))
                            {
                                while(!quit_opt){
                                    while (SDL_PollEvent(&event) != 0) {
                                        if (event.type == SDL_QUIT) {
                                            quit = 1;
                                        }
                                    }
                                    SDL_RenderClear(pRenderer);
                                    SDL_RenderCopy(pRenderer,pTextureMenuWallpaper, NULL, &menuWallpaper);
                                    if(aff_bout(pRenderer,&Choix_six,event,pTexturePersoSixHoover,pTexturePersoSix)){
                                        *choix_perso = 1;
                                        SDL_Delay(250);
                                        quit_opt = 1;
                                    }
                                    if(aff_bout(pRenderer,&Choix_mono,event,pTexturePersoMonoHoover,pTexturePersoMono)){
                                        *choix_perso = 2;
                                        SDL_Delay(250);
                                        quit_opt = 1;
                                    }
                                    if(aff_bout(pRenderer,&Opt_Quit,event,pTextureQuitPressButton,pTextureQuitButton)){
                                        quit_opt = 1;
                                    }
                                    SDL_RenderPresent(pRenderer);
                                }
                                SDL_Delay(200);
                                quit_opt = 0;
                            }
                            if (aff_bout(pRenderer,&quitButton,event,pTextureQuitPressButton,pTextureQuitButton))
                            {
                                quit_result=1;
                                quit=1;
                            }                            
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
            SDL_Delay(1000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
            SDL_DestroyWindow(pWindow);
        }
     else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();
    IMG_Quit();

    if(play_result==1)
        return 1;
    else if (quit_result == 1)
        return 0;
    
}