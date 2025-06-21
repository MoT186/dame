#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "tours.h"

void initialise_damier(Piece* damier[TAILLE][TAILLE])
{
    for(int i=0;i<TAILLE;i++)
    {
        for(int k=0;k<TAILLE;k++)
        {
            damier[i][k]=NULL;
        }
    }

    for(int ligne=0;ligne<4;ligne++){
        for(int a=0;a<TAILLE;a++){
        
            if((a+ligne)%2==1)
            {
                Piece* pion_blanc=malloc(sizeof(Piece));
                pion_blanc->couleur=BLANC;
                pion_blanc->type=PION;
                damier[ligne][a]=pion_blanc;
            }
        }
    }
    for(int ligne=6;ligne<10;ligne++){
        for(int a=0;a<TAILLE;a++){
        
            if((a+ligne)%2==1)
            {
                Piece* pion_noir=malloc(sizeof(Piece));
                pion_noir->couleur=NOIR;
                pion_noir->type=PION;
                damier[ligne][a]=pion_noir;
            }
        }
    }
}

void affiche_damier(Piece* damier[TAILLE][TAILLE])
{
    for(int i=0;i<TAILLE;i++){
        printf("%d |",i);
        for(int j=0;j<TAILLE;j++)
        {
            if(damier[i][j]==NULL)
            {
                printf(". ");
            }

            else if(damier[i][j]->couleur==BLANC )
            {
                if(damier[i][j]->type==PION){
                    printf("b ");
                }
                else{
                    printf("B ");
                }
            }

            else if(damier[i][j]->couleur==NOIR){
                if(damier[i][j]->type==PION){
                    printf("n ");
                }
                else{
                    printf("N ");
                }
            }
        }
        if(i!=9)
            printf("\n");
        else{
            printf("\n   ");
            for(int k=0;k<TAILLE;k++)
                printf("_ ");
            printf("\n   ");
            for(int l=0;l<TAILLE;l++)
                printf("%d ",l);
            printf("\n");
        }
    }
}

Joueur initialise_joueur(Couleur col)
{
    Joueur j;
    j.couleur=col;
    j.piece_initiale=20;
    j.piece_restante=20;
    return j;
}
