#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "grille.h"



extern long int random(void);

struct Case
{
   char couleur;
   int dedant;
};   


grille Grille(int taille)
{
        grille ret=NULL;
        ret=malloc(taille*taille*sizeof(Case));	
        return ret;
}


void Liberation(grille a)
{
    if(a!=NULL)
  {
    free(a);
    a=NULL;
  }
}

char constructeur()
{
    /*srand((unsigned)time(NULL));*/
    int i=random()%6+1;     
    char couleur;
    switch(i)
   {
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

int get_dedant(grille g) {
	return (g->dedant);
}

grille augemente_pointeur(grille g)
{
    g=g+1;
    return (g);
}

void init_grille(grille a,int taille)
{
     int i=0;
     for(i=0;i<taille*taille;i++)
     {
         a->couleur=constructeur();
         a=augemente_pointeur(a);
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






     
         






