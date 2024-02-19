// TP4 - Recherche du chemin le plus court avec une file
#include "../lib/labyrinthe.h"
#include "../lib/image.h"
#include "../lib/file.h"
#include "../lib/pile.h"

void init_lab(int lab[N][M]){
	//1ère étape pour la création du labyrinthe parfat : tout initialiser en bloc de terre (avec du vert au dessus)
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++)
			lab[i][j] = TERREVERTE;		
	}
}

int valides(int i, int j){
// renvoie 1 si i et j se trouve sur une case du labyrinthe
	return(i >= 0 && i < N && j >= 0 && j < M);
}

int est_NUIT(int i, int j, int lab[N][M]){
	return(valides(i, j) && lab[i][j] == NUIT);
}

int est_TERRE(int i, int j, int lab[N][M]){
	return(valides(i, j) && (lab[i][j] == TERREVERTE || lab[i][j] == TERRE));
}

int vide(int i, int j, int lab[N][M]){
//Aucune case voisine n'est une terre
	return (!est_TERRE(i + 2, j, lab) && !est_TERRE(i - 2, j, lab) && !est_TERRE(i, j + 2, lab) && !est_TERRE(i, j - 2, lab));
}

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
   for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(lab[i][j] == TERREVERTE && (lab[i - 1][j] == TERREVERTE || lab[i - 1][j] == TERRE))
				lab[i][j] = TERRE;
		}
   }
}

//***************************
// Partie recherche de chemin
//***************************

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
