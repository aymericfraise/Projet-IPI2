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

int main(){
  int tests_run=0;
  char *result = tests_grille();
  if (result != 0) {
     printf("%s\n", result);
  }
  else {
     printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
