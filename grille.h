/**
    \file grille.c
    \brief Permet d'allouer la memoire de taille*sizeof(case) pour grille g.
    \author Min Li
**/
#include<time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
    \struct Case
**/
typedef struct Case Case ,*grille;


/**
    \fn Grille(int taille)
    \param la taille
    \return Retourne un pointeur qui pointe la première case de grille.
**/
grille Grille(int taille);

/**
    \fn liberation(grille a)
    \param la grille a
    \return rien
    \brief Permet de libérer la memoire pointé par le pointeur a
**/
void liberation(grille g);

/**
    \fn constructeur()
    \param rien
    \return la couleur produite aléatoirement.
    \brief Permet de produire une couleur aléatoire
**/
char constructeur();

/**
    \fn get_couleur(grille g)
    \param Le pointeur sur la grille, éventuellement incrémenté pour accéder à une autre case que la première.
    \return Retourne un char correspondant à la couleur de la case.
    \brief Permet de récupérer la couleur de la case pointée par le pointeur g.
**/
void init_grille(grille ,int);

/**
    \fn get_dedans(grille g)
    \param grille g
    \return la valeur de dedans
    \brief Permet d'obtenir le dedans de la case pointé par le pointeur g
**/
char get_couleur(grille g);

/**
    \fn aug_g(grille g,int distance)
    \param grille g,int distance
    \return le pointeur
    \brief Permet d'augmenter la valeur de pointeur
**/
int get_dedans(grille g);

/**
    \fn change1(grille g,int taille,char couleur)
    \param grille g,int taille,char couleur
    \return rien
    \brief Permet de changer la couleur d'indice taille
**/
grille aug_g(grille g,int distance);

/**
    \fn change_dedans(grille g,int taille,int dedans)
    \param grille g,int taille,int dedans
    \return rien
    \brief Permet de changer la valeur d'indice taille
**/
void change1(grille g,int taille,char couleur);

/**
    \fn init_grille(grille a,int taille)
    \param grille a,int taille
    \return rien
    \brief Permet d'initialiser la grille par les couleurs aléatoires
**/
void change_dedans(grille g,int taille,int dedans);

/**
    \fn cree_fichier_de_couleur(int taille)
    \param int taille
    \return rien
    \brief Permet de créer un ficher qui contient les couleurs aléatoires
**/
void cree_fichier_de_couleur(int);

/**
    \fn init_grille_fichier(grille a,FILE *fp,int taille)
    \param grille a,FILE *fp,int taille
    \return rien.
    \brief Permet d'initialiser la grille par le fichier
**/
void init_grille_fichier(grille ,FILE *,int );
