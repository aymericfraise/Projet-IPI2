#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int main(int argc, char *argv[]) {
  /*int continuer = 1;*/
	SDL_Surface *ecran = NULL;
  /* SDL_Event event;*/
  const SDL_VideoInfo* info = NULL;
	SDL_Surface *ima=NULL;
	char couleur;
	int test;
	int j[6],i;
	int taille;
	int ligne,colonne;
  liste l=NULL;
  int coup,ww;
  printf("**************************\n");
  printf("Donnez la taille de grille : ");
  scanf("%d",&taille);
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    /* Failed, exit. */
    fprintf( stderr, "Video initialization failed : %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
  info = SDL_GetVideoInfo( );
  if( !info ) {
    /* This should probably never happen. */
    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }

	ecran=SDL_SetVideoMode(50*taille, 50*taille, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("COLOR FLOOD DE MYAJ", NULL);

  /*ima = SDL_LoadBMP("./cerise.bmp");*/
	/* fillScreen(ecran, 0,0,0);*/
  grille g=Grille(taille);
    init_grille(g,taille);
    affiche_SDL(g,taille,ecran);
    l=makel(0,l);
    l=composante(g,l,taille);
    /*input du nombre de coups*/
    printf("Donnez le nombre de coup : " );
    scanf("%d",&coup );
    printf("************************\n");
    ww =win(g,taille);
    for ( i = 0; i < 6; i++)
	  {
	    j[i]=0;
	  }
    while (!ww && coup>0) {
      clear();
      for ( i = 0; i < 6; i++)
	     {
	         j[i]=0;
	     }
	     affiche_SDL(g,taille,ecran);
       printf("Nombre de coup restant : %d\n",coup );
	     jouable(g,l,j,taille);
	     printjouable(j);
	     printf("Entrez la couleur choisie : ");
	     scanf(" %c",&couleur);
	     printf("************************\n");
	     /*scanf("%c",&couleur);*/

	    /*couleur=getc(stdin);*/
	     if(!((couleur=='B' && j[0]) || (couleur=='V' && j[1]) || (couleur=='R' && j[2]) || (couleur=='J' && j[3]) || (couleur=='M' && j[4]) || (couleur=='G' && j[5])))
	     {
		       printf("La couleur que cous avez donné n'est pas jouable.\n");
	     }
	     else
	     {
		       coup--;
	         changeall(g,l,couleur);
	         l=composante(g,l,taille);
	         ww=win(g,taille);
	     }
	  }
    /*affichage final*/
    clear();
	  affiche_SDL(g,taille,ecran);
    printf("Nombre de coup restant : %d\n",coup );
	  if (ww) {
	     printf("Victoire\n" );
	  } else {
	     printf("Defaite\n");
	  }

    getc(stdin);
    getc(stdin);
    SDL_Quit();
    return 0;
}
