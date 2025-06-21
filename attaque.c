#include <stdio.h>
#include <stdlib.h>
#include "damier.h"
#include "tours.h"
#include "attaque.h"

void attaque_pion(Piece* damier[TAILLE][TAILLE],Couleur joueur,int x,int y,int* i_pion,int ennemi_pion[20][4])
{
    int dep_possible[4][2]={ {1,1},{-1,1},{1,-1},{-1,-1} };
    for(int k=0;k<4;k++)
    {
        int nx=dep_possible[k][0];
        int ny=dep_possible[k][1];
        int dx=x+nx;
        int dy=y+ny;
        if(dx<TAILLE && dy<TAILLE && dx>=0 && dy>=0 &&damier[dx][dy]!=NULL)
        {
            if(damier[dx][dy]->couleur!=joueur)
            {
                int ddx=dx+nx;
                int ddy=dy+ny;
                if(ddx<TAILLE && ddy<TAILLE && ddx>=0 && ddy>=0)
                {
                    if(damier[ddx][ddy]==NULL)
                    {
                        ennemi_pion[*i_pion][0]=x;
                        ennemi_pion[*i_pion][1]=y;
                        ennemi_pion[*i_pion][2]=ddx;
                        ennemi_pion[*i_pion][3]=ddy;
                        (*i_pion)++;
                    }
                }
            }
        }
    }
}


void attaque_dame(Piece* damier[TAILLE][TAILLE],Couleur joueur,int x,int y,int* i_dame,int ennemi_dame[20][4])
{
    int dep_possible[4][2]={ {1,1},{-1,1},{1,-1},{-1,-1} };
    for(int k=0;k<4;k++)
    {
        int nx=dep_possible[k][0];
        int ny=dep_possible[k][1];
        int dx=x+nx;
        int dy=y+ny;
        int ennemi_trouve=0;

        while( dx<TAILLE && dx>=0 && dy<TAILLE && dy>=0)
        {
            if(damier[dx][dy]==NULL)
            {
                if(ennemi_trouve)
                {
                    ennemi_dame[*i_dame][0]=x;
                    ennemi_dame[*i_dame][1]=y;
                    ennemi_dame[*i_dame][2]=dx;
                    ennemi_dame[*i_dame][3]=dy;
                    (*i_dame)++;
                    break;
                }

            }
            else 
            {
                if(damier[dx][dy]->couleur==joueur){
                    break;
                }
                else{
                    if(!ennemi_trouve)
                    {
                        ennemi_trouve = 1;
                    }
                    else {
                        break;
                    }
                }
            }
            dx+=nx;
            dy+=ny;
        }

    }
}

void prise(Piece* damier[TAILLE][TAILLE], int x_att, int y_att, int x_arrivee, int y_arrivee,Joueur* defense)
{
    // Permet de savoir dans quelle diagonale on prend 
    int dx =(x_arrivee - x_att) >0 ? 1 : -1 ;
    int dy= (y_arrivee - y_att) >0 ? 1 : -1 ;

    int x= x_att + dx;
    int y= y_att + dy;
    
    while(x!=x_arrivee && y!= y_arrivee)
    {
        if(damier[x][y]!=NULL)
        {
            free(damier[x][y]);
            damier[x][y] = NULL;
            (*defense).piece_restante -= 1;
            break; // Une seule pièce prise
        }
        x += dx;
        y += dy;
    }
    damier[x_arrivee][y_arrivee] = damier[x_att][y_att];
    damier[x_att][y_att] = NULL;

}

int attaque_obligatoire(Piece* damier[TAILLE][TAILLE],Couleur joueur,int deja_attaque,int x_init,int y_init,Joueur* defense)
{
    int ennemi_pion[20][4]; //Liste des coordonnees des pieces ennemis attaquables par un pion
    int ennemi_dame[20][4];//Liste des coordonnees des pieces ennemis attaquables par une dame
    int i_pion=0;//compteur dans la liste des ennemis attaquables pion
    int i_dame=0;//compteur dans la liste des ennemis attaquables dame
    for(int a=0;a<20;a++)
        for(int b=0;b<4;b++)
        {
            ennemi_pion[a][b]=-1;
            ennemi_dame[a][b]=-1;
        }

            
    if(!deja_attaque){        
        for(int a=0;a<TAILLE;a++)
        {
            for(int b=0;b<TAILLE;b++)
            {
                if(damier[a][b]!=NULL && damier[a][b]->couleur==joueur)
                {
                    switch(damier[a][b]->type)
                    {
                        case(PION):
                            attaque_pion(damier,joueur,a,b,&i_pion,ennemi_pion);
                            break;
                        case(DAME):
                            attaque_dame(damier,joueur,a,b,&i_dame,ennemi_dame);
                            break;
                    }
                }
            }
        }
    }
    else{
        switch(damier[x_init][y_init]->type)
        {   
            case(PION):
                attaque_pion(damier,joueur,x_init,y_init,&i_pion,ennemi_pion);
                break;
            case(DAME):
                attaque_dame(damier,joueur,x_init,y_init,&i_dame,ennemi_dame);
                break;
        }
    }
    //Vérification si il existe des prises 
    if( i_pion==0 && i_dame==0 ) return 0;
    
    int ennemi_total[40][4];
    int total=0; 

        for (int i = 0; i < i_pion; i++) {
        for (int j = 0; j < 4; j++) {
            ennemi_total[total][j] = ennemi_pion[i][j];
        }
        total++;
    }

    for (int i = 0; i < i_dame; i++) {
        for (int j = 0; j < 4; j++) {
            ennemi_total[total][j] = ennemi_dame[i][j];
        }
        total++;
    }

    printf("Choisissez une prise parmi les options suivantes :\n");
    for (int i = 0; i < total; i++) {
        printf("%d: De (%d,%d) -> (%d,%d)\n", i,
               ennemi_total[i][0], ennemi_total[i][1],
               ennemi_total[i][2], ennemi_total[i][3]);
    }

    int choix = -1;
    int legal=0;
    //printf("total :%d\n",total);
    do {
        printf("Votre choix : ");
        if(scanf("%d", &choix)!=1)
        {
            while(getchar()!='\n');
            continue;
        }
        while(getchar()!='\n');
        if(choix>= total || choix <0 )
        {
            continue ;
        }
        legal = 1;
        
    } while (!legal && (choix < 0 || choix >= total));

    int x1 = ennemi_total[choix][0];
    int y1 = ennemi_total[choix][1];
    int x2 = ennemi_total[choix][2];
    int y2 = ennemi_total[choix][3];

    prise(damier, x1, y1, x2, y2, defense);
    affiche_damier(damier);


    attaque_obligatoire(damier, joueur, 1, x2, y2, defense);
    return 1;
}
