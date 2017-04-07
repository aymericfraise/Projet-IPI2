#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"
#include "naif.h"








void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}




int set_sz_rect(int taille,int* width)
{
    if(*width%taille!=0)
    {
      *width=(*width/taille)*taille;
    }
    return *width/taille;
}

Uint8* clik_change(SDL_Surface *ecran)
{
   SDL_Event event;
   int autoDraw=0;
   Uint8 *p;
   while(1)
    {
       SDL_WaitEvent(&event);
      if (event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
      {
        int x,y;
        x = event.button.x ;
        y = event.button.y ;
        int bpp = ecran->format->BytesPerPixel;
        p = (Uint8 *)ecran->pixels + y * ecran->pitch + x * bpp;
        break;
       }
     }
     return p;
}



char find_couleur(Uint8 * p)
{
         char c;
        if(p[2]==0 && p[1]==0 && p[0]==255)
           c='B';
        else if(p[2]==0 && p[1]==100 && p[0]==0)
           c='V';
        else if (p[2]==255 && p[1]==0 && p[0]==0)
           c='R';
        else if (p[2]==255 && p[1]==185 && p[0]==15)
           c='J';
         else if (p[2]==139 && p[1]==69 && p[0]==19)
           c='M';
         else if (p[2]==139 && p[1]==87 && p[0]==66)
           c='G';
          return c;
}


int  couleur_marche(int j[],char couleur){
     int ret=0;
      if (j[0]==1 && couleur=='B')
        ret=1;
      if (j[1]==1 && couleur=='V')
        ret=1;
      if (j[2]==1 && couleur=='R')
        ret=1;
      if (j[3]==1 && couleur=='J')
        ret=1;
      if (j[4]==1 && couleur=='M')
        ret=1;
      if (j[5]==1 && couleur=='G')
        ret=1;
      return ret;
}









int main(int argc, char *argv[]) {

        int width=500;
        int height=700;
	SDL_Surface *ecran = NULL;
        const SDL_VideoInfo* info = NULL;
	SDL_Surface *ima=NULL;
	char couleur;
	int test;
	int j[6],i;
	int taille;
	int ligne,colonne;
        int sz_rect;
        Uint8 *p;
  liste l=NULL;
  int coup,ww;
  printf("**************************\n");
  printf("Donnez la taille de grille(10~24) : ");
  scanf("%d",&taille);
  sz_rect=set_sz_rect(taille,&width);
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    fprintf( stderr, "Video initialization failed : %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
  info = SDL_GetVideoInfo( );
  if( !info ) {
    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
	ecran=SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("COLOR FLOOD DE MYAJ", NULL);
	  ima = SDL_LoadBMP("./cerise.bmp");
	  fillScreen(ecran, 255,255,255);
	  grille g=Grille(taille);
	    init_grille(g,taille);
	    affiche_SDL(g,taille,ecran,sz_rect);
	    l=makel(0,l);
	    l=composante(g,l,taille);

	    int max=(taille*taille);
	    int	* mmax=&max;
			char gg[taille*taille+1];
	     coup=oui(g,taille,mmax,0,gg);
	    printf("Donnez le nombre de coup :%d ",coup );
	    ww =win(g,taille);
    



    while (!ww && coup>0) {
                 for ( i = 0; i < 6; i++)
	        {
	         j[i]=0;
                }
                 jouable(g,l,j,taille);
                 printjouable(j);
                 p=clik_change(ecran);
		 couleur=find_couleur(p);
           if(!couleur_marche(j,couleur) )
	     {
		       printf("La couleur que cous avez donné n'est pas jouable.\n");
                       continue;
              }
                  coup--;
	         changeall(g,l,couleur);
                 affiche_SDL(g,taille,ecran,sz_rect);
	         l=composante(g,l,taille);
	         ww=win(g,taille);}
		    getc(stdin);
		    getc(stdin);
		    SDL_Quit();
		    return 0;
}
