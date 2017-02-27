/**
  \file [<couleur.c>]
  \brief {contient les fonction de couleurs}
  \author {Min,Yoann}
**/

#include<time.h>
#include <stdbool.h>
#include <stdlib.h>
#include<stdio.h>
#include"grille.h"
#include"couleur.h"


/**
  \struct liste
**/
struct t_liste {
  int position;
  struct t_liste *suivant;
};

/**
  \fn int listevide(liste l)
  \param liste à tester
  \return 1 si vide 0 sinon
**/
int listevide(liste l){return (l==NULL);}

/**
  \fn liste makel(int d,liste l)
  \param entier tete de la nouvelle liste
  \param liste queue de la nouvelle liste
  \return la nouvelle liste
**/
liste makel(int d,liste l){
  cell *c;
  c=(cell *)malloc(sizeof(cell));
  c->position=d;
  c->suivant =l;
  return c;
}

/**
  \fn liste sui(liste l)
  \param liste dont on veut le suivant
  \return la queue de la liste
**/
liste sui(liste l){
  return l->suivant;
}

/**
  \fn int pop(liste l)
  \param liste dont on veut la tete
  \return la tete de la liste
**/
int pop(liste l){
  return l->position;
}

/**
  \fn int pop(liste l)
  \param liste a liberer
**/
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

/**
  \fn liste composante(grille g,liste l,int taille)
  \param la grille de jeu
  \param la liste de la composante a l'etat i-1 (marche avec la liste a n'importe quel etat anterieur)
  \param taille de la grille
  \return la liste de la composante
**/
liste composante(grille g,liste l,int taille){
  liste ret=NULL;
  int i;
  liste temps=NULL;
  while (l!=NULL) {
    i=pop(l);
    temps=l;
    l=sui(l);
    free(temps);
    ret=makel(i,ret);
    if (i%taille!=0 && !(get_dedans(aug_g(g,i-1))) &&  get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i-1))){
      change_dedans(g,i-1,1);
      l=makel(i-1,l);
     /* printf("%d ",i-1);*/
    }
    if (i%taille!=taille-1 && !(get_dedans(aug_g(g,i+1))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i+1))) {
      change_dedans(g,i+1,1);
      l=makel(i+1,l);
      /*printf("%d",i+1);*/
    }
    if (i/taille!=0 && !(get_dedans(aug_g(g,i-taille))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i-taille))) {
      change_dedans(g,i-taille,1);
      l=makel(i-taille,l);
      /*printf("%d",i-taille);*/
    }
    if (i/taille!=taille-1 && !(get_dedans(aug_g(g,i+taille))) && get_couleur(aug_g(g,i))==get_couleur(aug_g(g,i+taille))) {
      change_dedans(g,i+taille,1);
      l=makel(i+taille,l);
     /* printf("%d",i+taille);*/
    }
  }
  
  return ret;
}

/**
  \fn void changeall(grille g,liste l,char couleur)
  \param la grille de jeu
  \param la liste a changer
  \param la couleur a metre
**/
void changeall(grille g,liste l,char couleur) {
  if (l!=NULL) {
    change1(g,l->position,couleur);
    changeall(g,l->suivant,couleur);
  }
}

/**
  \fn int win(grille g,int taille)
  \param la grille de jeu
  \param la taille de la grille
  \return 1 en cas de victoire 0 sinon
**/
int win(grille g,int taille){
  int i;
  for (i = 0;i < taille*taille; i++)
  {
     if(get_dedans(aug_g(g,i)) ==0)
      return 0;
   }
   return 1;
}
