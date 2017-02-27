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


grille Grille(int taille)
{
     grille ret=NULL;
     ret=malloc(taille*taille*sizeof(Case));	
     return ret;
}


void liberation(grille a)
{
     free(a);
}

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
 

char get_couleur(grille g) {
    return (g->couleur);
}

int get_dedans(grille g) {
    return (g->dedans);
}

grille aug_g(grille g,int distance)
{
    g=g+distance;
    return (g);
}

void change1(grille g,int taille,char couleur)
{
       g=aug_g(g,taille);
       g->couleur=couleur;
}

void change_dedans(grille g,int taille,int dedans)
{
      g=aug_g(g,taille);
      g->dedans=dedans;
}

void init_grille(grille a,int taille)
{
    int i=0;
    for(i=0;i<taille*taille;i++)
    {
         a->couleur=constructeur();
         a=aug_g(a,1);
    }
}


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


void init_grille_fichier(grille a,FILE *fp,int taille)
{
     int i=0;
     for(i=0;i<taille*taille;i++)
     {
         a[i].couleur=fgetc(fp);
     }
     fclose(fp); 
}






     
         






