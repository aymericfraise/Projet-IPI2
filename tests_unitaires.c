#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "grille.h"
#include "couleur.h"


void tests_grille(){
  grille g = Grille(5);
  init_grille(g,5);
  /*test de get_dedans*/
  CU_assert(get_dedans(g)==1);
  /*test de change1*/
  change1(g,5,'R');
  CU_assert(get_couleur(aug_g(g,5))=='R');
  change1(g,5,'G');
  CU_assert(get_couleur(aug_g(g,5))=='G');
  /*test de change_dedans*/
  change_dedans(g,5*5-1,1);
  CU_assert(get_dedans(aug_g(g,5*5-1))==1);
  change_dedans(g,5*5-1,0);
  CU_assert(get_dedans(aug_g(g,5*5-1))==0);
  return 0;
}

void test_init_fichier(){
  FILE *file=fopen("fichiers_de_test/test_init_fichier.dat","w+");
  grille g = Grille(4);
  g = init_grille_fichier(g,file,4)
  int validation = 1;
  int i;
  /*tout doit etre initialisé à B*/
  for(i=0;i<16;i++;){
    if(get_couleur(aug_g(g,i)!='B') validation = 0;
  }
  CU_assert(validation);
}


void test_changeall(){
  FILE *file=fopen("fichiers_de_test/test_changeall.dat","w+");
  grille g = Grille(4);
  g = init_grille_fichier(g,file,4);
  liste comp_connexe;
  comp_connexe = composante(aug_g(g,6), comp_connexe, 4);
  changeall(g,comp_connexe,'R');
  int validation=1;
  for(i=0;i<16;i++){
    if(get_couleur(aug_g(g,i))!='R') validation = 0;
  }
  CU_assert(validation);
}

void test_win(){
  FILE *fwin=fopen("fichiers_de_test/test_win","w+");
  FILE *flose=fopen("fichiers_de_test/test_lose","w+");
  grille gwin = Grille(4);
  grille glose = Grille(4);
  gwin = init_grille_fichier(g,fwin,4);
  glose = init_grille_fichier(g,flose,4);
  liste l = NULL;
  l = makel(0,l);
  composante(gwin,l,4);
  composante(glose,l,4);
  CU_assert(win(gwin,4)==1);
  CU_assert(lose(glose,4)==0);
}

static char * all_tests(){
  CU_basic_run_test(tests_grille);
  CU_basic_run_test(test_changeall);
  CU_basic_run_test(test_win);
  return 0;
}

int main(){
  CU_pSuite pSuite = NULL;
  CU_initialize_registry();
  pSuite = CU_add_suite("Suite",NULL,NULL);
  CU_add_test(pSuite,"tests_grille",tests_grille);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return result != 0;
}
