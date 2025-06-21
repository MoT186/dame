#ifndef TOURS_H
    #define TOURS_H

    int dep_possible(Piece* damier[TAILLE][TAILLE],int x,int y,Couleur couleur);
    void deplacement(Piece* damier[TAILLE][TAILLE],Couleur joueur);
    void promotion(Piece* damier[TAILLE][TAILLE]);
    void tour(Piece* damier[TAILLE][TAILLE],Couleur joueur,Joueur *defense);
#endif
