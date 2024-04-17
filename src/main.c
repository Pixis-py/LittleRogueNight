#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../lib/menu.h"
#include "../lib/anim.h"
#include "../lib/image.h"

#define NB_PV_JOUEUR 100

int main(){
    int choice = 0;
    int * choix_perso = malloc(sizeof(int)); /*Permet à l'utilisateur de choisir son personnage dans le menu*/
    *choix_perso = 0;
    printf("Program launch...\n");
    choice = menu(0, NULL,choix_perso); // Lancement du menu
    while(choice !=0){
        if(choice == 1){
            int lab[N][M];
            creer_lab(lab);
            if(chercher_chemin(lab, N - 1, M - 1, 0, 0)){ 
                if(*choix_perso == 0){/*Cas ou l'utilisateur choisi de jouer avec six*/
                    character_t * six; // Déclaration du personnage
                    create(&six,NB_PV_JOUEUR); // Création du personnage
                    choice = anim(0, NULL, lab, &six); // Boucle de jeu (labyrinthe et animation)
                    destruct(&six); // Destruction du personnage
                }
                if(*choix_perso == 1){ /*Cas ou l'utilisateur choisi de jouer avec mono*/
                    character_t * mono; // Déclaration du personnage
                    create(&mono,NB_PV_JOUEUR); // Création du personnage
                    choice = anim(0, NULL, lab, &mono); // Boucle de jeu (labyrinthe et animation)
                    destruct(&mono); // Destruction du personnage
                }
            }
        }
    }
    free(choix_perso);
    choix_perso=NULL;
    printf("Program exit...\n");
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé normalement
}


