#include<time.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h>

/*définition de la structure de la grille*/
typedef struct Case Case ,*grille;
 

/*créer une grille de taille int*/
grille Grille(int taille);
/*liberer la memoire pour la grille g*/
void liberation(grille g);
/*créer une couleur aléatoire*/
char constructeur();
/*initialisation de la grille par les couleurs aléatoires*/
void init_grille(grille ,int);
/*obtenir la couleur de permiere case de grille g*/
char get_couleur(grille g);
/*obtenir le dedans de permiere case de grille g*/
int get_dedans(grille g);
/*augmenter le pointeur de grille g*/
grille aug_g(grille g,int distance);
/*creer le ficher de couleur*/
void change1(grille g,int taille,char couleur);
void change_dedans(grille g,int taille,int dedans);
void cree_fichier_de_couleur(int);
/*initialisation de la grille par les couleurs dans le  fichier*/
void init_grille_fichier(grille ,FILE *,int );


