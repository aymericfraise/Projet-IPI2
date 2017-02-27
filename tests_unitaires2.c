#include <stdio.h>
#include "grille.h"
#include "couleur.h"

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
int tests_run = 0;


static char * tests_grille(){
  grille g = Grille(5);
  init_grille(g,5);
  /*test de get_dedans*/
  /*mu_assert("erreur get_dedans", get_dedans(g)==1);*/
  /*test de change1*/
  change1(g,5,'R');
  mu_assert("erreur change1",get_couleur(aug_g(g,5))=='R');
  change1(g,5,'G');
  mu_assert("erreur change1", get_couleur(aug_g(g,5))=='G');
  /*test de change_dedans*/
  change_dedans(g,5*5-1,1);
  mu_assert( "erreur change_dedans",get_dedans(aug_g(g,5*5-1))==1);
  change_dedans(g,5*5-1,0);
  mu_assert( "erreur change_dedans",get_dedans(aug_g(g,5*5-1))==0);
  return 0;
}

static char * test_init_fichier(){
  FILE *file=fopen("fichiers_de_test/test_init_fichier.dat","w+");
  grille g = Grille(4);
  init_grille_fichier(g,file,4);
  int validation = 1;
  int i;
  /*tout doit etre initialisé à B*/
  for(i=0;i<16;i++){
    if(get_couleur(aug_g(g,i))!='B') validation = 0;
  }
  mu_assert("erreur init_fichier",validation);
  return 0;
}


static char * test_changeall(){
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
  mu_assert("erreur changeall",validation);
  return 0;
}

static char * test_win(){
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
  mu_assert("erreur win",win(gwin,4)==1);
  mu_assert("erreur lose",win(glose,4)==0);
  return 0;
}

static char * all_tests(){
  mu_run_test(tests_grille);
  mu_run_test(test_init_fichier);
  mu_run_test(test_changeall);
  mu_run_test(test_win);
  return 0;
}

int main(){
  char *result = all_tests();
  if (result != 0) {
     printf("%s\n", result);
  }
  else {
     printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
