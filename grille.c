#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "grille.h"



extern long int random(void);

struct Case
{
     char couleur;
     int dedans;
};   

/**
    \file grille.c
    \brief Permet d'allouer la memoire de taille*sizeof(case) pour grille g.
    \author Min Li
**/

/**
    \struct 
**/

/**
    \fn Grille(int taille)
    \param la taille 
    \return Retourne un pointeur qui pointe la première case de grille.
**/
grille Grille(int taille)
{
     grille ret=NULL;
     ret=malloc(taille*taille*sizeof(Case));	
     return ret;
}

/**
    \file grille.c
    \brief Permet de libérer la memoire pointé par le pointeur a
    \author Min Li
**/

/**
    \struct 
**/

/**
    \fn liberation(grille a)
    \param la grille a 
    \return rien.
**/
void liberation(grille a)
{
     free(a);
}

/**
    \file grille.c
    \brief Permet de produire une couleur aléatoire
    \author Min Li
**/

/**
    \struct:switch case
**/

/**
    \fn constructeur()
    \param rien
    \return la couleur produite aléatoirement.
**/




char constructeur()
{
    int i=random()%6+1;     
    char couleur;
    switch(i){
        case 1:couleur='B';break;
        case 2:couleur='V';break;
        case 3:couleur='R';break;
        case 4:couleur='J';break;
        case 5:couleur='M';break;
        case 6:couleur='G';break;
        default:break;
    }
    return couleur;
}
 
/**
    \file grille.c
    \brief Permet de récupérer la couleur de la case pointée par le pointeur g.
    \author Min Li
**/

/**
    \struct 
**/

/**
    \fn get_couleur(grille g)
    \param Le pointeur sur la grille, éventuellement incrémenté pour accéder à une autre case que la première.
    \return Retourne un char correspondant à la couleur de la case.
**/
char get_couleur(grille g) {
    return (g->couleur);
}

/**
    \file grille.c
    \brief Permet d'obtenir le dedans de la case pointé par le pointeur g
    \author Min Li
**/

/**
    \struct
**/

/**
    \fn get_dedans(grille g)
    \param grille g
    \return la valeur de dedans.
**/

int get_dedans(grille g) {
    return (g->dedans);
}

/**
    \file grille.c
    \brief Permet d'augmenter la valeur de pointeur
    \author Min Li
**/

/**
    \struct
**/

/**
    \fn aug_g(grille g,int distance)
    \param grille g,int distance
    \return le pointeur.
**/
grille aug_g(grille g,int distance)
{
    g=g+distance;
    return (g);
}
/**
    \file grille.c
    \brief Permet de changer la couleur d'indice taille
    \author Min Li
**/

/**
    \struct
**/

/**
    \fn change1(grille g,int taille,char couleur)
    \param grille g,int taille,char couleur
    \return rien.
**/
void change1(grille g,int taille,char couleur)
{
       g=aug_g(g,taille);
       g->couleur=couleur;
}
/**
    \file grille.c
    \brief Permet de changer la valeur d'indice taille
    \author Min Li
**/

/**
    \struct
**/

/**
    \fn change_dedans(grille g,int taille,int dedans)
    \param grille g,int taille,int dedans
    \return rien.
**/
void change_dedans(grille g,int taille,int dedans)
{
      g=aug_g(g,taille);
      g->dedans=dedans;
}

/**
    \file grille.c
    \brief Permet d'initialiser la grille par les couleurs aléatoires
    \author Min Li
**/

/**
    \struct
**/

/**
    \fn init_grille(grille a,int taille)
    \param grille a,int taille
    \return rien.
**/
void init_grille(grille a,int taille)
{
    int i=0;
    change_dedans(a,0,1);
    for(i=0;i<taille*taille;i++)
    {
   
         a->couleur=constructeur();
         a=aug_g(a,1);
    }
}

/**
    \file grille.c
    \brief Permet de créer un ficher qui contient les couleurs aléatoires
    \author Min Li
**/

/**
    \struct:for
**/

/**
    \fn cree_fichier_de_couleur(int taille)
    \param int taille
    \return rien.
**/
void cree_fichier_de_couleur(int taille)
{
    FILE *fp=fopen("couleur.dat","w+");
    int i;
    for(i=0;i<taille*taille;i++)
    {
        fputc(constructeur(),fp);
    }
    fclose(fp);
}

/**
    \file grille.c
    \brief Permet d'initialiser la grille par le fichier
    \author Min Li
**/

/**
    \struct:for
**/

/**
    \fn init_grille_fichier(grille a,FILE *fp,int taille)
    \param grille a,FILE *fp,int taille
    \return rien.
**/
void init_grille_fichier(grille a,FILE *fp,int taille)
{
     int i=0;
     change_dedans(a,0,1);
     for(i=0;i<taille*taille;i++)
     {
         a[i].couleur=fgetc(fp);
     }
     fclose(fp); 
}






     
         






