#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"
#include "naif.h"
#include "graphe3.h"








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
   /*int autoDraw=0;*/
   Uint8 *p;
   while(1)
    {
       SDL_WaitEvent(&event);
       if(event.type==SDL_QUIT)
       {
             SDL_Quit();
             break;
        }
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


int  couleur_marche(int j[6],char couleur){
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



/*choisir le mode de jouer*/

int mode_jouer(/*SDL_Surface *ecran,*/int coup/*int taille,int sz_rect*/)
{
    SDL_Event event;
   while(1)
    {
       SDL_WaitEvent(&event);
      if (event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
      {
        int x,y;
        x = event.button.x ;
        y = event.button.y ;
        if(x>=10 && x<=140 && y>=610&& y<=610+65)
            { coup+=10;break;}
        else if(x>=160 && x<=290 && y>=610 && y<=610+65)
            { coup+=5;break;}
        else if(x>=330 && x<=500 && y>=610 && y<=610+65)
            { coup=coup;break;}
      }
    }
      return coup;
}










int main() {
  srand((unsigned)time(NULL));
  int width=560;
  int height=700;
  SDL_Surface *ecran = NULL;
  char couleur;
  int j[6],i;
  int taille;
  SDL_Event event;
  int sz_rect;
  Uint8 *p;
  liste l=NULL;
  int coup,ww;
  SDL_Init( SDL_INIT_VIDEO );
  ecran=SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  taille=saisir_taille(ecran);
  width=500;
  sz_rect=set_sz_rect(taille,&width);
  /*SDL_FreeSurface(ecran);
  SDL_VideoQuit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();*/
  ecran=SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("COLOR FLOOD DE MYAJ", NULL);
	fillScreen(ecran, 255,255,255);
  grille g=Grille(taille);
  init_grille(g,taille);
  /*solveur*/
  int a;
  char* g_col = malloc(sizeof(char)*taille*taille); //grille des couleurs des pixels
  int* g_comp = malloc(sizeof(int)*taille*taille); //grille des composantes des pixels
  for (a = 0; a < taille*taille; a++) {
    g_col[a]=get_couleur(g,a);
    g_comp[a]=get_dedans(g,a);
  }


  /*initialise le graphe*/
  Graphe* g1 = graphe_init(taille);

  /*initialise les composantes*/
  mark_all_comp(g1, g_col,g_comp,taille);



  /*trouve les voisins de chaque composante*/
  trouve_voisins(g1, g_comp, taille);

  char* solution = calloc(g1->nb_comp,sizeof(char));
  int max = g1->nb_comp;
  solveur(g1, solution, 0, &max, taille);
  int *mmax=&max;
   coup = *mmax+1;
  printf("%d\n",max );
  free(g_col);
  free(g_comp);
	free(solution);

  int b;
  for (a = 0; a < g1->nb_comp; a++) {
    for (b = 0; b < 6; b++) {
      freell(g1->comps[a]->voisins[b]);
    }
    free(g1->comps[a]->voisins);
    free(g1->comps[a]->nb_voisins);
    free(g1->comps[a]);
  }

  free(g1->comps);
	free(g1->pris);
	free(g1);
  /*fin solveur*/
  
  //*mmax=max;
	/*printf("Le jeu peut être fini en %d coup\n",coup);*/
	affiche_SDL(g,taille,ecran,sz_rect,coup,*mmax+1,1,0);
  coup=mode_jouer(/*ecran,*/coup/*taille,sz_rect*/);
  *mmax=coup-1;
  affiche_SDL(g,taille,ecran,sz_rect,coup,*mmax+1,0,0 );
	l=makel(0,l);
	l=composante(g,l,taille);
  ww =win(g,taille);
  /******************************************************/
  while (!ww && coup>0)
{
	    for ( i = 0; i < 6; i++)
	    {
	      j[i]=0;
	    }
	    jouable(g,l,j,taille);
	    /*printjouable(j);*/
	    p=clik_change(ecran);
	    couleur=find_couleur(p);
	    if(!couleur_marche(j,couleur))
            {
	       printf("La couleur que vous avez donné n'est pas jouable.\n");
	       continue;
	    }
	    coup--;
       changeall(g,l,couleur);
       l=composante(g,l,taille);
       ww=win(g,taille);
       affiche_SDL(g,taille,ecran,sz_rect,coup,*mmax+1,0,ww);
}
       freel(l);

      while(1)
     {
       SDL_WaitEvent(&event);
      if(event.type==SDL_QUIT)
	     {
         SDL_Quit();
        break;
       }
    }
            liberation(g);
	    return 0;
	}
