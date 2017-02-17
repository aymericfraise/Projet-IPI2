#include<stdio.h>
#include <stdlib.h>
#include "grille.h"












int main()
{
    int taille;
    int i;
    FILE* fp=fopen("couleur.dat","r");
    printf("Donnez la taille de grille :");
    scanf("%d",&taille);
    grille g=Grille(taille);
    /*************************************************/
    printf("ici,c'est le résultat d'initialisation à partir de valeurs aléatoires:\n");
    init_grille(g,taille);
    grille g1=g;
    for(i=0;i<taille*taille;i++)
    {
        printf("%c ",get_couleur(g1));
        g1=augmente_pointeur(g1);
        if(i%taille==taille-1)
            printf("\n");
    }   
    
     /******************************************************************/
    printf("Résultat d'initialisation à partir de valeurs contenue dans un fichier:\n");
    cree_fichier_de_couleur(taille);
    init_grille_fichier(g,fp,taille);
    grille g2=g;
    for(i=0;i<taille*taille;i++){
        printf("%c ",get_couleur(g2));
        g2=augmente_pointeur(g2);
        if(i%taille==taille-1)
            printf("\n");
    }    
    liberation(g);

    return 0;
}
