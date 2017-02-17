#include<stdio.h>
#include <stdlib.h>
#include "grille.h"


void grille_couleur_init_aleatoire(grille g, int taille){
    int i;  
    init_grille(g,taille);
    printf("Résultat d'initialisation à partir de valeurs aléatoires:\n");  
    for(i=0;i<taille*taille;i++)
    {
        printf("%c ",get_couleur(g));
        g=augmente_pointeur(g);
        if(i%taille==taille-1)
            printf("\n");
    }  
}

void grille_couleur_init_fichier(grille g, FILE* fp, int taille){
    int i;
    printf("Résultat d'initialisation à partir de valeurs contenue dans un fichier:\n");
    /*Creation du fichier qui sera utilise pour établir la grille. Comparer le fichier à l'affichage assure
      le bon fonctionnement de la fonction.*/
    cree_fichier_de_couleur(taille);
    init_grille_fichier(g,fp,taille);
    for(i=0;i<taille*taille;i++){
        printf("%c ",get_couleur(g));
        g=augmente_pointeur(g);
        if(i%taille==taille-1)
            printf("\n");
    }    
}

int main()
{
    /*Initialisation de la variable random pour la détermination de la grille*/
    srand(time(NULL));

    /*Déclaration des variables*/
    int taille;

    /*Ouverture du fichier de la grille de test*/
    FILE* fp=fopen("couleur.dat","r");

    /*Initialisation de la taille de la grille*/
    printf("Donnez la taille de grille :");
    scanf("%d",&taille);
    grille g = Grille(taille);

    /*Test de la creation de grille avec des couleurs aleatoire pour chaque case*/
    grille_couleur_init_aleatoire(g, taille);
 
    
    /*Test de la creation de la grille a partir de la fonction*/
    grille_couleur_init_fichier(g, fp, taille);

    /*Liberation de la memoire*/
    liberation(g);

    return 0;
}
