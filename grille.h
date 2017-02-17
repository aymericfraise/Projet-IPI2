#include<time.h>
#include <stdbool.h> 
#include <stdlib.h>

typedef struct Case Case ,*grille;
 


grille Grille(int);

void liberation(grille);

char constructeur();

void init_grille(grille ,int);

char get_couleur(grille );

int get_dedans(grille );

grille augmente_pointeur(grille );

void cree_fichier_de_couleur(int);

void init_grille_fichier(grille ,FILE *,int );


