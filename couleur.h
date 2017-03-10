#include<time.h>
#include <stdbool.h>


/**
  \struct liste
**/
typedef struct t_liste cell,*liste;

/**
  \fn int listevide(liste l)
  \param liste à tester
  \return 1 si vide 0 sinon
**/
int listevide(liste l);

/**
  \fn liste makel(int d,liste l)
  \param entier tete de la nouvelle liste
  \param liste queue de la nouvelle liste
  \return la nouvelle liste
**/
liste makel(int d,liste l);

/**
  \fn liste sui(liste l)
  \param liste dont on veut le suivant
  \return la queue de la liste
**/
liste sui(liste l);

/**
  \fn int pop(liste l)
  \param liste dont on veut la tete
  \return la tete de la liste
**/
int pop(liste l);

/**
  \fn int pop(liste l)
  \param liste a liberer
**/
void freel(liste l);

/**
  \fn liste composante(grille g,liste l,int taille)
  \param la grille de jeu
  \param la liste de la composante a l'etat i-1 (marche avec la liste a n'importe quel etat anterieur)
  \param taille de la grille
  \return la liste de la composante
**/
liste composante(grille,liste,int);


/**
  \fn void changeall(grille g,liste l,char couleur)
  \param la grille de jeu
  \param la liste a changer
  \param la couleur a metre
**/
void changeall(grille g,liste l,char c);

/**
  \fn int win(grille g,int taille)
  \param la grille de jeu
  \param la taille de la grille
  \return 1 en cas de victoire 0 sinon
**/
int win(grille,int);
