#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "tours.h"


int dep_possible(Piece* damier[TAILLE][TAILLE],int x,int y,Couleur couleur)
{
    int hx=x+1; int hy=y+1; int bx=x-1; int by=y-1;
    switch (couleur)
    {
        case BLANC:
            //déplacement en bas des pions blancs (on prend en compte que 0 0 est le coin supérieur gauche et 9 9)
            if( (hx<TAILLE && hy<TAILLE && damier[hx][hy]==NULL) || (hx<TAILLE && by>=0 && damier[hx][by]==NULL)){
                return 1;
            }
            break;
            
        case NOIR:
            //déplacement en haut des pions noirs
            if( (bx>=0 && by>=0 && damier[bx][by]==NULL) || (bx>0 && hy<TAILLE && damier[bx][hy]==NULL ) ){
                return 1;
            }
            break;
    }
    return 0;
}

void dep_pion(Piece* damier[TAILLE][TAILLE], int x, int y, int x_arrive,int y_arrive)
{
    damier[x_arrive][y_arrive]=damier[x][y];
    damier[x][y]=NULL;
}

void deplacement_pion(Piece* damier[TAILLE][TAILLE], Couleur joueur, int x, int y)
{   
    int x_arr,y_arr;
    int coup_possible = 0;
    do{
        printf("Choississez une case d'arrivee: ");
        if(scanf("%d %d",&x_arr,&y_arr)!=2 || x_arr>=TAILLE || y_arr>=TAILLE || x_arr<0 || y_arr<0 || damier[x_arr][y_arr]!=NULL)
        {
            while (getchar()!='\n');
            continue;
        }

        switch(joueur)
        {
            case (NOIR):
                if(x_arr == x-1 && (y_arr == y+1 || y_arr == y-1))
                    while (getchar()!='\n');
                    coup_possible = 1;
                break;


            case(BLANC):
                if(x_arr == x+1 && (y_arr == y+1 || y_arr == y-1))   
                    while (getchar()!='\n');                
                    coup_possible = 1;                    
                break;
        }
        if(!coup_possible){
            printf("Entree invalide reessayer\n");
            while(getchar()!='\n');
        }
    }while(!coup_possible);

    dep_pion(damier,x,y,x_arr,y_arr);
}


void deplacement(Piece* damier[TAILLE][TAILLE],Couleur joueur)
{
    int legit=0;
    int x,y;

    //vérification de la pièce séléctionné (peut-elle se déplacer ?)
    do{
        printf("\nChoisissez une piece avec ses coordonnees: ");
        if(scanf("%d %d",&x,&y)!=2)
        {
            while(getchar()!='\n');
            continue;
        }
        if(x>=TAILLE || x<0 || y>=TAILLE || y<0 || (x + y) %2!=1)
        {
            while(getchar()!='\n');
            printf("Il n'y a pas de piece ici");
            continue;            
        }
        if(damier[x][y]==NULL || damier[x][y]->couleur!=joueur)
        {
            while(getchar()!='\n');
            continue;   
        }
        if(!dep_possible(damier,x,y,joueur))
        {
            while(getchar()!='\n');
            continue;       
        }
        while(getchar()!='\n');
        deplacement_pion(damier,joueur,x,y);
        legit = 1;

    }while(!legit);

}

