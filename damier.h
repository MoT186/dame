#ifndef DAMIER_H
    #define DAMIER_H
    #define TAILLE 10

        typedef enum{PION, DAME} TypePiece ;
        typedef enum {BLANC , NOIR} Couleur;

        typedef struct{
            TypePiece type;
            Couleur couleur;
        }Piece;

        typedef struct{
            Couleur couleur;
            int piece_restante;
            int piece_initiale;
        }Joueur;

        void initialise_damier(Piece* damier[TAILLE][TAILLE]);
        void affiche_damier(Piece* damier[TAILLE][TAILLE]);

        Joueur initialise_joueur(Couleur col);
#endif
