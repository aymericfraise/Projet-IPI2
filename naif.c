#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"

void oui(grille g,int taille,int* max,int it,char gg[]){
  int j[6],i;
  char a='0';

  for ( i = 0; i < 6; i++){
    j[i]=0;
  }

  grille g1=NULL;
  g1=Grille(taille);
  change_dedans(g1,0,1);
  for ( i = 0; i < taille*taille; i++) {
    a=get_couleur(g,i);
    change1(g1,i,a);
  }

  liste l=makel(0,NULL);
  l=composante(g1,l,taille);
  if (win(g1,taille)) {
    gg[it]='\0';
    printf("solution trouvee en %d coups : %s\n",it,gg );
    *max=it-1;
  }
  else if (it<*max) {
    jouable( g1, l,j, taille);
    if (j[0]) {
      changeall(g1,l,'B');
      gg[it]='B';
      oui(g1,taille,max,it+1,gg);
    }
    if (j[1]) {
      changeall(g1,l,'V');
      gg[it]='V';
      oui(g1,taille,max,it+1,gg);
    }
    if (j[2]) {
      changeall(g1,l,'R');
      gg[it]='R';
      oui(g1,taille,max,it+1,gg);
    }
    if (j[3]) {
      changeall(g1,l,'J');
      gg[it]='J';
      oui(g1,taille,max,it+1,gg);
    }
    if (j[4]) {
      changeall(g1,l,'M');
      gg[it]='M';
      oui(g1,taille,max,it+1,gg);
    }
    if (j[5]) {
      changeall(g1,l,'G');
      gg[it]='G';
      oui(g1,taille,max,it+1,gg);
    }
  }

  liberation(g1);
  freel(l);
}
