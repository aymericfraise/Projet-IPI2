#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include"grille.h"
#include"couleur.h"

/*definition de la structure de liste d'entier*/
struct t_liste {
  int position;
  struct t_liste *suivant;
};

/*renvoie 1 si la liste est vide 0 sinon*/
int listevide(liste l){return (l==NULL);}

/*ajoute l'element d a la liste l*/
liste makel(int d,liste l){
  cell *c;
  c=(cell *)malloc(sizeof(cell));
  c->position=d;
  c->suivant =l;
  return c;
}

/*renvoie la queue de la liste*/
liste sui(liste l){
  return l->suivant;
}

/*renvoie la tete de la liste*/
int pop(liste l){
  return l->position;
}

/*libere la memore pour les liste*/
void freel(liste l){
  if (l!=NULL) {
    freel(l->suivant);
    free(l);
  }
}

/*donne a la case i de la grille g la valeur c*/
/*void change1(grille g,int i,char c);*/
/*renvoie la liste des position des cases appartenant a la composante connexe*/
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
    if (i%taille!=0 && !(get_dedans(g,i-1)) &&  get_couleur(g,i)==get_couleur(g,i-1)){
      change_dedans(g,i-1,1);
      l=makel(i-1,l);
     /* printf("%d ",i-1);*/
    }
    if (i%taille!=taille-1 && !(get_dedans(g,i+1)) && get_couleur(g,i)==get_couleur(g,i+1)) {
      change_dedans(g,i+1,1);
      l=makel(i+1,l);
      /*printf("%d",i+1);*/
    }
    if (i/taille!=0 && !(get_dedans(g,i-taille)) && get_couleur(g,i)==get_couleur(g,i-taille)) {
      change_dedans(g,i-taille,1);
      l=makel(i-taille,l);
      /*printf("%d",i-taille);*/
    }
    if (i/taille!=taille-1 && !(get_dedans(g,i+taille)) && get_couleur(g,i)==get_couleur(g,i+taille)) {
      change_dedans(g,i+taille,1);
      l=makel(i+taille,l);
     /* printf("%d",i+taille);*/
    }
  }

  return ret;
}

/*donne au case de laliste l dans la grille g la valeur c*/
void changeall(grille g,liste l,char couleur) {
  if (l!=NULL) {
    change1(g,l->position,couleur);
    changeall(g,l->suivant,couleur);
  }
}

/*renvoie 1 en cas de victoire 0 sinon*/
int win(grille g,int taille){
  int i;
  for (i = 0;i < taille*taille; i++)
  {
     if(get_dedans(g,i) ==0)
      return 0;
   }
   return 1;
}
