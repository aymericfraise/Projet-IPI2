#include<time.h>
#include <stdbool.h>
#include <stdlib.h>
#include<stdio.h>
#include"grille.h"
#include"couleur.h"



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

/*void change1(grille g,int i,char couleur){
  g=aug_g(g,i);
  g->couleur=couleur;
}*/

liste composante(grille g,liste l,int taille){
  liste ret=NULL;
  int i;
  while (l!=NULL) {
    i=pop(l);
    l=sui(l);
    ret=makel(i,ret);
    if (i%taille!=0 && !(get_dedans(aug_g(g,i-1))) &&  get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i-1))){
      change_dedans(g,i-1,1);
      l=makel(i-1,l);
    }
    if (i%taille!=taille-1 && !(get_dedans(aug_g(g,i+1))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i+1))) {
      change_dedans(g,i+1,1);
      l=makel(i+1,l);
    }
    if (i/taille!=0 && !(get_dedans(aug_g(g,i-taille))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i-taille))) {
      change_dedans(g,i-taille,1);
      l=makel(i-taille,l);
    }
    if (i/taille!=taille-1 && !(get_dedans(aug_g(g,i+taille))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i+taille))) {
      change_dedans(g,i+taille,1);
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
  for (i = 0;i < taille*taille; i++)
  {
     if(get_dedans(aug_g(g,i)) ==0)
      return 0;
   }
   return 1;
}
