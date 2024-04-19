#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../lib/menu.h"
#include "../lib/anim.h"
#include "../lib/image.h"

#define NB_PV_JOUEUR 100

int main(){
    int choice = 0;
    srand(time(NULL));
    int * choix_perso = malloc(sizeof(int)); /*Permet à l'utilisateur de choisir son personnage dans le menu*/
    *choix_perso = 0;
    printf("Program launch...\n");
    choice = menu(0, NULL,choix_perso); // Lancement du menu
    while(choice !=2){
        if(choice == 1){
            int lab[N][M];
            creer_lab(lab);
            if(chercher_chemin(lab, N - 1, M - 1, 0, 0)){ 
                if(*choix_perso == 0){/*Cas ou l'utilisateur choisi de jouer avec six*/
                    character_t * six; // Déclaration du personnage
                    create(&six,NB_PV_JOUEUR, 25); // Création du personnage
                    choice = anim(0, NULL, lab, 1, &six);
                    if(choice == 1){
                        creer_lab(lab);
                        if(chercher_chemin(lab, N - 1, M - 1, 0, 0) == 1){
                            choice = anim(0, NULL, lab, 2, &six);
                            if(choice == 1){
                                creer_lab(lab);
                                if(chercher_chemin(lab, N - 1, M - 1, 0, 0) == 1)
                                    choice = anim(0, NULL, lab, 3, &six);
                                    if(choice == 1)
                                        choice = 2;
                            }
                        }
                    }
                    destruct(six); // Destruction du personnage
                    choice = menu(0, NULL,choix_perso);
                }
            }
            if(*choix_perso == 1){ /*Cas ou l'utilisateur choisi de jouer avec mono*/
                character_t * mono; // Déclaration du personnage
                create(&mono,NB_PV_JOUEUR, 50); // Création du personnage
                choice = anim(0, NULL, lab, 1, &mono);
                creer_lab(lab);
                if(chercher_chemin(lab, N - 1, M - 1, 0, 0) == 1){
                    choice = anim(0, NULL, lab, 2, &mono);
                    creer_lab(lab);
                    if(chercher_chemin(lab, N - 1, M - 1, 0, 0) == 1)
                        choice = anim(0, NULL, lab, 3, &mono);
                }
                destruct(mono); // Destruction du personnage
                choice = menu(0, NULL,choix_perso);
            }
        }
    }
    free(choix_perso);
    choix_perso=NULL;
    printf("Program exit...\n");
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé normalement
}


