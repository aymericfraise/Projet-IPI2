#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "naif.h"
#include "exSDL.h"


void tests_grille(){
  grille g = Grille(5);
  init_grille(g,5);
  /*test de get_dedans*/
  /*CU_ASSERT(get_dedans(g,1)==1);*/
  /*test de change1*/
  change1(g,5,'R');
  CU_ASSERT(get_couleur(g,5)=='R');
  change1(g,5,'G');
  CU_ASSERT(get_couleur(g,5)=='G');
  /*test de change_dedans*/
  change_dedans(g,5*5-1,1);
  CU_ASSERT(get_dedans(g,5*5-1)==1);
  change_dedans(g,5*5-1,0);
  CU_ASSERT(get_dedans(g,5*5-1)==0);
  free(g);
}

void test_init_fichier(){
  FILE *file=fopen("fichiers_de_test/test_init_fichier.dat","r");
  grille g = Grille(4);
  init_grille_fichier(g,file,4);
  int validation = 1;
  int i;
  /*tout doit etre initialisé à B*/
  for(i=0;i<16;i++){
    if(get_couleur(g,i)!='B') validation = 0;
  }
  CU_ASSERT(validation);
  free(g);
  fclose(file);
}


void test_changeall(){
  FILE *file=fopen("fichiers_de_test/test_changeall.dat","r");
  grille g = Grille(4);
  init_grille_fichier(g,file,4);
  liste comp_connexe = NULL;
  comp_connexe = makel(0,comp_connexe);
  comp_connexe = composante(g, comp_connexe, 4);
  changeall(g,comp_connexe,'R');
  int validation=1;
  int i;
  for(i=0;i<16;i++){
    if(get_couleur(g, i)!='R') validation = 0;
  }
  CU_ASSERT(validation);
  freel(comp_connexe);
  free(g);
  fclose(file);
}

void test_win(){
  FILE *fwin=fopen("fichiers_de_test/test_win.dat","r");
  FILE *flose=fopen("fichiers_de_test/test_lose.dat","r");
  grille gwin = Grille(4);
  grille glose = Grille(4);
  init_grille_fichier(gwin,fwin,4);
  init_grille_fichier(glose,flose,4);

  liste l = makel(0,NULL);
  l = composante(gwin,l,4);
  CU_ASSERT(win(gwin,4)==1);
  freel(l);

  l = makel(0,NULL);
  l = composante(glose,l,4);
  CU_ASSERT(win(glose,4)==0);
  freel(l);

  free(gwin);
  free(glose);
  fclose(fwin);
  fclose(flose);
}

/*-------------------------------------------------------------------*/
/*Tests unitaires du solveur*/

void test_oui(){
  int res;
  int max = 6;
  int it = 0;
  char gg[5];
  FILE *file=fopen("fichiers_de_test/test_oui.dat","r");
  grille g = Grille(5);
  init_grille_fichier(g, file,5);
  oui(g,5,&max,it,gg);
  printf("\"vrai\" solution : %s\n",gg);
  CU_ASSERT((max+1)==5 && gg[0]=='G' && gg[1]=='M' && gg[2]=='R' && gg[3]=='V' && gg[4]=='G');

  fclose(file);
}

/*-------------------------------------------------------------------*/
/*main de test*/

int main(){
  CU_pSuite pSuite = NULL;
  CU_initialize_registry();
  pSuite = CU_add_suite("Suite",NULL,NULL);
  CU_add_test(pSuite,"tests_grille",tests_grille);
  CU_add_test(pSuite,"tests_init_fichier",test_init_fichier);
  CU_add_test(pSuite,"tests_changeall",test_changeall);
  CU_add_test(pSuite,"tests_test_win",test_win);
  CU_add_test(pSuite,"tests_test_oui",test_oui);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();



  return 0;
}
