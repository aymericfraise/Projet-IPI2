#include<stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "couleur.h"

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

    
    grille h=Grille(taille);
    init_grille(h,taille);
    /*on change chaque case de h une par une pour la metre en rouge*/
    for ( i = 0; i < taille*taille; i++) {
      change1(h,i,'R');
    }
    printf("\n" );
    for ( i = 0; i < taille*taille; i++) {
      printf("%c ",get_couleur1(h[i]));
      if(i%taille==taille-1)
          printf("\n");
    }
    liste k=NULL;
    k=makel(0,k);
    k=composante(h,k,taille);
    
    /*la liste est initialisée a 0*/
    liste l=NULL;
    l=makel(0,l);
    
    /*on recupere la composante connexe*/
    l=composante(g,l,taille);
    
    /*on affiche la liste et la grille pour verifier*/
    k=composante(g,l,taille);
    while (!(listevide(k))) {
      printf("%d ",pop(k));
      k=sui(k);
    }
    printf("\n" );
     for ( i = 0; i < taille*taille; i++) {
      printf("%c ",get_couleur1(g[i]));
      if(i%taille==taille-1)
          printf("\n");
    }
    printf("\n" );
    
    /*on utilise changeall et verifie le resultat*/
    changeall(g,l,'M');
    for ( i = 0; i < taille*taille; i++) {
      printf("%c ",get_couleur1(g[i]));
      if(i%taille==taille-1)
          printf("\n");
    }
    printf("\n" );
    l=composante(g,l,taille);
    changeall(g,l,'B');
    for ( i = 0; i < taille*taille; i++) {
      printf("%c ",get_couleur1(g[i]));
      if(i%taille==taille-1)
          printf("\n");
    }
    
    /*on teste win sur h et g*/
    printf("victoire sur g %d\n",win(g,taille) );
    printf("victoire sur h %d\n",win(h,taille) );
    
    /*Liberation de la memoire*/
    liberation(g);
    liberation(h);
    freel(l);
    freel(k);

    return 0;
}