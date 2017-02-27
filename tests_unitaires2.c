#include <stdio.h>
#include "grille.h"
#include "couleur.h"
#include "minunit.h"

MU_TEST(tests_grille){
  grille g = Grille(5);
  init_grille(g,5);
  /*test de get_dedans*/
  /*mu_check("erreur get_dedans", get_dedans(g)==1);*/
  /*test de change1*/
  change1(g,5,'R');
  mu_check(get_couleur(aug_g(g,5))=='R');
  change1(g,5,'G');
  mu_check(get_couleur(aug_g(g,5))=='G');
  /*test de change_dedans*/
  change_dedans(g,5*5-1,1);
  mu_check(get_dedans(aug_g(g,5*5-1))==1);
  change_dedans(g,5*5-1,0);
  mu_check(get_dedans(aug_g(g,5*5-1))==0);
}

MU_TEST(test_init_fichier){
  FILE *file=fopen("fichiers_de_test/test_init_fichier.dat","w+");
  grille g = Grille(4);
  init_grille_fichier(g,file,4);
  int validation = 1;
  int i;
  /*tout doit etre initialisé à B*/
  for(i=0;i<16;i++){
    if(get_couleur(aug_g(g,i))!='B') validation = 0;
  }
  mu_check(validation);
}


MU_TEST(test_changeall){
  FILE *file=fopen("fichiers_de_test/test_changeall.dat","w+");
  grille g = Grille(4);
  init_grille_fichier(g,file,4);
  liste comp_connexe = NULL;
  comp_connexe = makel(0,comp_connexe);
  comp_connexe = composante(aug_g(g,6), comp_connexe, 4);
  changeall(g,comp_connexe,'R');
  int validation=1;
  int i;
  for(i=0;i<16;i++){
    if(get_couleur(aug_g(g,i))!='R') validation = 0;
  }
  mu_check(validation);
}

MU_TEST(test_win){
  FILE *fwin=fopen("fichiers_de_test/test_win","w+");
  FILE *flose=fopen("fichiers_de_test/test_lose","w+");
  grille gwin = Grille(4);
  grille glose = Grille(4);
  init_grille_fichier(gwin,fwin,4);
  init_grille_fichier(glose,flose,4);
  liste l = NULL;
  l = makel(0,l);
  composante(gwin,l,4);
  composante(glose,l,4);
  mu_check(win(gwin,4)==1);
  mu_check(win(glose,4)==0);
}

MU_TEST_SUITE(test_suite){
  MU_RUN_TEST(tests_grille);
  MU_RUN_TEST(test_init_fichier);
  MU_RUN_TEST(test_changeall);
  MU_RUN_TEST(test_win);
}

int main(){
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
