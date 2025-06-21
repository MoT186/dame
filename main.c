#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "tours.h"


int main(){

    Piece* damier[TAILLE][TAILLE];
    initialise_damier(damier);
    affiche_damier(damier);

    Joueur j1 = initialise_joueur(BLANC);
    Joueur j2 = initialise_joueur(NOIR);
    
    do{
        tour(damier,BLANC,&j2);
        promotion(damier);
        affiche_damier(damier);
        printf("Blanc: %d || Noir: %d\n\n", j1.piece_restante, j2.piece_restante);

        tour(damier,NOIR,&j1);
        promotion(damier);
        affiche_damier(damier);
        printf("Blanc: %d || Noir: %d\n\n", j1.piece_restante, j2.piece_restante);

    }while(j1.piece_restante>0 && j2.piece_restante>0);
    
    if(j1.piece_restante==0)
    {
        printf("Victoire des noirs!!\n");
    }
    else{
        printf("Victoire des blancs!!\n");
    }

    return 0;
}
