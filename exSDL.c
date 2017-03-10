
#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
/*
 compilation soous Linux : gcc -o exSDL exSDL.c -lSDL
 compilation sur Mac : gcc -o exSDL -I/Library/Frameworks/SDL.framework/Headers  exSDL.c SDLmain.m -framework SDL -framework Cocoa
*/

int autoDraw=0;

// px, py coordonnées haut, gauche de la texture
void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima) {
	SDL_Rect rect;
    rect.x=px;
    rect.y=py;
	SDL_BlitSurface(ima, NULL, ecran, &rect);
	SDL_Flip(ecran);
}

// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

// px, py coordonnées haut, gauche du pixel
void drawPixel(SDL_Surface *ecran, int px, int py, int r, int g, int b) {
    drawRectangle(ecran,  px,  py, 1,  r,  g,  b);
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}



void upi(char c,int i[]){
  if (c=='B' ) {
    i[0]=1;
  }
  else if (c=='V') {
    i[1]=1;
  }
  else if (c=='R') {
    i[2]=1;
  }
  else if (c=='J') {
    i[3]=1;
  }
  else if (c=='M') {
    i[4]=1;
  }
  else if (c=='G') {
    i[5]=1;
  }
}

void jouable(grille g,liste l,int i[6],int taille){
   if (!listevide(l)) {
    int a=pop(l);
    if (a%taille!=0 && get_couleur(aug_g(g,a-1))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a-1)),i);
    }
    if (a%taille!=taille-1 && get_couleur(aug_g(g,a+1))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a+1)),i);
    }
    if (a/taille!=0 && get_couleur(aug_g(g,a-taille))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a-taille)),i);
    }
    if (a/taille!=taille-1 && get_couleur(aug_g(g,a+taille))!=get_couleur(aug_g(g,a))) {
      upi(get_couleur(aug_g(g,a+taille)),i);
    }
     jouable(g,sui(l),i,taille);
  }
}

void printjouable(int j[6]){
  printf("les couleurs qu'on peut choisir:");
  if (j[0]) {
    printf("B " );
  }
  if (j[1]) {
    printf("V " );
  }
  if (j[2]) {
    printf("R " );
  }
  if (j[3]) {
    printf("J " );
  }
  if (j[4]) {
    printf("M " );
  }
  if (j[5]) {
    printf("G " );
  }
 printf("\n");
}



void affiche_SDL(grille g,int taille,SDL_Surface *ecran/*,int coup*/)
{
   int i,ligne,colonne;
   char couleur;
   for(i=0;i<taille*taille;i++)
         {
             couleur=get_couleur(aug_g(g,i));
             switch (couleur) {
             case 'B':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 0, 0, 255);break;}
             case 'V':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 0, 100, 0);break;}
             case 'R':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 255, 0, 0);break;}
             case 'J':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 255, 185,15);break;}
             case 'M':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 139, 69, 19);break;}
             case 'G':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*50, colonne*50, 50, 139, 87, 66);break;}
             }
          }
    /*printf("nombre de coup restant:%d\n",coup );*/
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
    printf("Donnez la taille de grille :");
    scanf("%d",&taille);
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
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
        printf("Donnez le nombre de coup:" );
        scanf("%d",&coup );
        printf("************************\n");
        ww =win(g,taille);
         for ( i = 0; i < 6; i++) 
	    {
	      j[i]=0;
	    }
       while (!ww && coup>0) {
           for ( i = 0; i < 6; i++) 
	    {
	      j[i]=0;
	    }
	     affiche_SDL(g,taille,ecran);
             printf("nombre de coup restant:%d\n",coup );
	     jouable(g,l,j,taille);
	     printjouable(j);
	     printf("donnez la couleur choisie:");
	     scanf(" %c",&couleur);
	     printf("************************\n");
	     /*scanf("%c",&couleur);*/
	     
	     /*couleur=getc(stdin);*/
	     if(!((couleur=='B' && j[0]) || (couleur=='V' && j[1]) || (couleur=='R' && j[2]) || (couleur=='J' && j[3]) || (couleur=='M' && j[4]) || (couleur=='G' && j[5])))
	     {
		 printf("la couleur que cous avez donné n'est pas jouable\n");   
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
	  affiche_SDL(g,taille,ecran);
          printf("nombre de coup restant:%d\n",coup );
	  if (ww) {
	    printf("victoire\n" );
	  } else {
	    printf("defaite\n");
	  }

        
      



    
    /*while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_p:
                        drawRectangle(ecran, 250, 250, 2, 255, 255, 255);
                        drawRectangle(ecran, 0, 0, 10, 255, 0, 0);
                        drawPixel(ecran, 1, 1, 0, 255, 0);
                        drawPixel(ecran, 0, 0, 0, 0, 255);

                        break;
            		case SDLK_e:
                        fillScreen(ecran, 255,0,255);
						break;
                    case SDLK_r:
                        fillScreen(ecran, 0,0,0);
                        break;
                    case SDLK_t :
                        drawTexture(ecran, 100, 150, ima);
                        break;
            		case SDLK_ESCAPE:
						continuer=0; break;
            	}
            	break;
                
            case SDL_MOUSEBUTTONUP:
                autoDraw=0;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    drawRectangle(ecran, event.button.x, event.button.y, 3, 255, 0, 0);
                }
                               break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    autoDraw=1;
                    drawRectangle(ecran, event.button.x, event.button.y, 3, 0, 255, 0);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    int x,y;
                    x = event.button.x ;
                    y = event.button.y ;
                    int bpp = ecran->format->BytesPerPixel;*/
                    /* Here p is the address to the pixel we want to retrieve */
                   /* Uint8 *p = (Uint8 *)ecran->pixels + y * ecran->pitch + x * bpp;
                    fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[0], p[1], p[2]);
                }
                break;
            case SDL_MOUSEMOTION:
                if (autoDraw)
                    drawRectangle(ecran, event.button.x, event.button.y, 1, 0, 0, 255);
                
                break;

                
                
        }
    }*/
       getc(stdin);
       getc(stdin);
       SDL_Quit();
	return 0;
}
