#ifndef ATTAQUE_H
    #define ATTAQUE_H
    #include "damier.h"

    void attaque_pion(Piece* damier[TAILLE][TAILLE],Couleur joueur,int x,int y,int* compteur_tab_prise,int ennemi_attaquable[20][4]);
    void prise(Piece* damier[TAILLE][TAILLE], int x_att, int y_att, int x_arrivee, int y_arrivee,Joueur *defense);
    int attaque_obligatoire(Piece* damier[TAILLE][TAILLE],Couleur joueur,int deja_attaque,int x_init,int y_init,Joueur *defense);

#endif
