#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "tours.h"
#include "attaque.h"



void promotion(Piece* damier[TAILLE][TAILLE])
{
    for(int i=0;i<TAILLE;i++)
   {
        if(damier[9][i]!=NULL && damier[9][i]->type==PION && damier[9][i]->couleur==BLANC)
        {
            damier[9][i]->type=DAME;
        }
        else if(damier[0][i]!=NULL && damier[0][i]->type==PION && damier[0][i]->couleur==NOIR)
        {
            damier[0][i]->type=DAME;
        }
    }
}


void tour(Piece* damier[TAILLE][TAILLE],Couleur joueur,Joueur *defense)
{
    printf("Au tour des ");
    switch (joueur)
    {
        case BLANC:
            printf("Blancs\n");
            break;
        case NOIR:
            printf("Noirs\n");
            break;
        default :
            printf("Error\n");
            exit(1);
    }
    if(!attaque_obligatoire(damier,joueur,0,-1,-1,defense))
    {
        deplacement(damier,joueur);
    }
}
