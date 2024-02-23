#include <stdlib.h>
#include <stdio.h>
#include "../lib/bouton.h"
#include "../lib/menu.h"
#include "../lib/anim.h"
#include "../lib/image.h"
#include "../lib/labyrinthe.h"

int main(){
    int choice = 0;
    printf("Program launch...\n");
    choice = menu(0, NULL); // Lancement du menu
    while(choice !=0){
        if(choice == 1){
            int lab[N][M];
            creer_lab(lab);
            if(chercher_chemin(lab, N - 1, M - 1, 0, 0))
                choice = anim(0, NULL, lab); // Boucle de jeu (labyrinthe et animation)
        }
    }
    printf("Program exit...\n");
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé normalement
}


