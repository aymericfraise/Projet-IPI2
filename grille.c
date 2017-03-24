#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"grille.h"

extern long int random(void);

/*définition de la structure de la grille*/
struct Case
{
     char couleur;
     int dedans;
};


grille Grille(int taille)
{
     grille ret=NULL;
     ret=calloc(taille*taille,sizeof(Case));
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


char get_couleur(grille g,int i) {
    return (g[i].couleur);
}

int get_dedans(grille g,int i) {
    return (g[i].dedans);
}



void change1(grille g,int i,char couleur)
{
       g[i].couleur=couleur;
}

void change_dedans(grille g,int i,int dedans)
{
      g[i].dedans=dedans;
}

void init_grille(grille a,int taille)
{
    int i=0;
    change_dedans(a,0,1);
    for(i=0;i<taille*taille;i++)
    {

         a[i].couleur=constructeur();
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
     change_dedans(a,0,1);
     for(i=0;i<taille*taille;i++)
     {
         a[i].couleur=fgetc(fp);
     }
     fclose(fp);
}
