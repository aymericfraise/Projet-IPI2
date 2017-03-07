#include<stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "couleur.h"
#include <time.h>


void affiche(grille g,int taille,int coup){
  int i;
  for ( i = 0; i < taille*taille; i++) {
      printf("%c ",get_couleur(aug_g(g,i)));
      if(i%taille==taille-1){
          printf("\n");
      }
  }
  printf("nb de coup restant%d\n",coup );
}

void upi(char c,int i[]){
  if (c=='B' ) {
    i[0]=1;
  }
  if (c=='V') {
    i[1]=1;
  }
  if (c=='R') {
    i[2]=1;
  }
  if (c=='J') {
    i[3]=1;
  }
  if (c=='M') {
    i[4]=1;
  }
  if (c=='G') {
    i[5]=1;
  }
}

void jouable(grille g,liste l,int i[6],int taille){
  if (!listevide(l)) {
    int a=pop(l);
    if (a%taille!=0 && get_couleur(aug_g(g,a-1))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a-1)),i);
    }
    if (a%taille!=taille-1 && get_couleur(aug_g(g,a+1))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a+1)),i);
    }
    if (a/taille!=0 && get_couleur(aug_g(g,a-taille))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a-taille)),i);
    }
    if (a/taille!=taille-1 && get_couleur(aug_g(g,a+taille))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a+taille)),i);
    }
    jouable(g,sui(l),i,taille);
  }
}

void printjouable(int j[6]){
  if (j[0]) {
    printf("B " );
  }
  if (j[1]) {
    printf("V " );
  }
  if (j[2]) {
    printf("R " );
  }
  if (j[3]) {
    printf("J " );
  }
  if (j[4]) {
    printf("M " );
  }
  if (j[5]) {
    printf("G " );
  }
}

int main(int argc, char const *argv[]) {
  char couleur;
  int j[6],i;
  /*input de la taille*/
  int taille;
  printf("Donnez la taille de grille :");
  scanf("%d",&taille);
  /*initialisation de la grille*/
  grille g=Grille(taille);
  init_grille(g,taille);
  /*initialisation de la liste*/
  liste l=NULL;
  l=makel(0,l);
  l=composante(g,l,taille);

  /*input du nombre de coups*/
  int coup;
  printf("\nnb de coup:" );
  scanf("%d\n",&coup );
  /*boucle de jeu*/
  int ww =0;
  while (!ww && coup>0) {
    for ( i = 0; i < 6; i++) {
      j[i]=0;
    }
    jouable(g,l,j,taille);
    affiche(g,taille,coup);
    coup--;
    do {
      printf("couleur a jouer:");
      printjouable(j);
      scanf("%c\n",&couleur );
    } while(!((couleur=='B' && j[0]) || (couleur=='V' && j[1]) || (couleur=='R' && j[2]) || (couleur=='J' && j[3]) || (couleur=='M' && j[4]) || (couleur=='G' && j[5])));

    changeall(g,l,couleur);
    l=composante(g,l,taille);
    ww=win(g,taille);
  }
  /*affichage final*/
  affiche(g,taille,coup);
  if (ww) {
    printf("victoire\n" );
  } else {
    printf("defaite\n");
  }
  return 0;
}
