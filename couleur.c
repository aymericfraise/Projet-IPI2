#include<time.h>
#include <stdbool.h>
#include <stdlib.h>
#include"grille.h"
#include"couleur.h"
#include<stdio.h>

struct t_liste {
  int position;
  struct t_liste *suivant;
};

int listevide(liste l){return (l==NULL);}

liste makel(int d,liste l){
  cell *c;
  c=(cell *)malloc(sizeof(cell));
  c->position=d;
  c->suivant =l;
  return c;
}

liste sui(liste l){
  return l->suivant;
}

int pop(liste l){
  return l->position;
}

void freel(liste l){
  if (l!=NULL) {
    freel(l->suivant);
    free(l);
  }
}

void change1(grille g,int i,char couleur){
  g[i].couleur=couleur;
}

liste composante(grille g,liste l,int taille){
  liste ret=NULL;
  int i;
  while (l!=NULL) {
    i=pop(l);
    l=sui(l);
    ret=makel(i,ret);
    if (i%taille!=0 && !(g[i-1].dedans) && g[i].couleur==g[i-1].couleur){
      g[i-1].dedans=1;
      printf("j'ajoute %d a ma liste\n",i-1 );
      l=makel(i-1,l);
    }
    if (i%taille!=taille-1 && !(g[i+1].dedans) && g[i].couleur==g[i+1].couleur) {
      g[i+1].dedans=1;
      printf("j'ajoute %d a ma liste\n",i+1 );
      l=makel(i+1,l);
    }
    if (i/taille!=0 && !(g[i-taille].dedans) && g[i].couleur==g[i-taille].couleur) {
      g[i-taille].dedans=1;
      printf("j'ajoute %d a ma liste\n",i-taille);
      l=makel(i-taille,l);
    }
    if (i/taille!=taille-1 && !(g[i+taille].dedans) && g[i].couleur==g[i+taille].couleur) {
      g[i+taille].dedans=1;
      printf("j'ajoute %d a ma liste\n",i+taille );
      l=makel(i+taille,l);
    }
  }
  return ret;
}

void changeall(grille g,liste l,char couleur) {
  if (l!=NULL) {
    change1(g,l->position,couleur);
    changeall(g,l->suivant,couleur);
  }
}

int win(grille g,int taille){
  int i;
  for (i = 0;g[i].dedans && i < taille*taille; i++)
  i=g[i].dedans;
  return i;
}
