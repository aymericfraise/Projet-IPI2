#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "grille.h"
#include "couleur.c"


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
}

void tests_couleur(){
  grille g = Grille(5);
  init_grille(g, 5);

}

int main(){
  CU_pSuite pSuite = NULL;
  CU_initialize_registry();
  pSuite = CU_add_suite("Suite",NULL,NULL);
  CU_add_test(pSuite,"tests_grille",tests_grille);
  CU_add_test(pSuite,"tests_couleur",tests_couleur);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
