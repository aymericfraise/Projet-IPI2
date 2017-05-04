#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"
#include "SDL/SDL_ttf.h"
/*
 compilation soous Linux : gcc -o exSDL exSDL.c -lSDL
 compilation sur Mac : gcc -o exSDL -I/Library/Frameworks/SDL.framework/Headers  exSDL.c SDLmain.m -framework SDL -framework Cocoa
*/

int autoDraw=0;

// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
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
    if (a%taille!=0 && get_couleur(g,a-1)!=get_couleur(g,a)) {
      upi(get_couleur(g,a-1),i);
    }
    if (a%taille!=taille-1 && get_couleur(g,a+1)!=get_couleur(g,a)) {
      upi(get_couleur(g,a+1),i);
    }
    if (a/taille!=0 && get_couleur(g,a-taille)!=get_couleur(g,a)) {
      upi(get_couleur(g,a-taille),i);
    }
    if (a/taille!=taille-1 && get_couleur(g,a+taille)!=get_couleur(g,a)) {
      upi(get_couleur(g,a+taille),i);
    }
     jouable(g,sui(l),i,taille);
  }
}


void printjouable(int j[6]){
  printf("Les couleurs jouables pour le prochain coup : ");
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

void affiche_SDL(grille g,int taille,SDL_Surface *ecran,int sz_rect,int coup,int mmax,int flag)
{
    
   SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   int i,ligne,colonne;
   char couleur;
   
    int a=100;
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
   /* SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);*/
    char msg[100]="\n";
    sprintf(msg,"coup: %d/%d",coup,mmax);
    police = TTF_OpenFont("angelina.ttf", 65);
    texte = TTF_RenderText_Blended(police, msg, couleurNoire);
    
    
    for(i=0;i<taille*taille;i++)
         {
             couleur=get_couleur(g,i);
             switch (couleur) {
             case 'B':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 0, 0, 255);break;}
             case 'V':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 0, 100, 0);break;}
             case 'R':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 255, 0, 0);break;}
             case 'J':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 255, 185,15);break;}
             case 'M':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 139, 69, 19);break;}
             case 'G':{ligne=i/taille;colonne=i%taille;drawRectangle(ecran, ligne*sz_rect, colonne*sz_rect, sz_rect, 139, 87, 66);break;}
             }
          } 

/*le premier initialisation*/
   if(flag==1)
  {
     while (continuer)
    {
        police = TTF_OpenFont("angelina.ttf", 50);
        position.x = 10;
        position.y = taille*sz_rect+sz_rect/2;
        sprintf(msg,"choisissez votre mode de jouer:");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        police = TTF_OpenFont("angelina.ttf", 65);
        position.x = 10;
        position.y = taille*sz_rect+sz_rect;
        sprintf(msg,"facile");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 160;
        position.y = taille*sz_rect+sz_rect;
        sprintf(msg,"moyen");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 330;
        position.y = taille*sz_rect+sz_rect;
        sprintf(msg,"difficile");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */

        SDL_Flip(ecran);
        break;
     }
 }
     
 else if( flag==0)
 {

   while (continuer)
    {
        position.x = sz_rect;
        position.y = taille*sz_rect+sz_rect;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        break;
     }
 }
      
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    TTF_Quit();

  
}





int saisir_taille(SDL_Surface *ecran)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   int i,ligne,colonne;
   char couleur;
   int taille=3;
    int a=100;
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
   /* police = TTF_OpenFont("angelina.ttf", 50);*/
    police = TTF_OpenFont("Quaterback Fight.ttf", 30);
    char msg[100]="\n";
   sprintf(msg,"COLOR FLOOD DE MYAJ");
   texte = TTF_RenderText_Blended(police, msg, couleurNoire);
    while (continuer)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x = 50;
        position.y = 100;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        police = TTF_OpenFont("2.ttf", 30);
        position.x = 10;
        position.y = 300;
        sprintf(msg,"CHOISISSEZ LA TAILLE:");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        position.x = 200;
        position.y = 400;
        sprintf(msg,"+ %d -",taille);
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        position.x = 300;
        position.y = 550;
        sprintf(msg,"ON Y VA!");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        SDL_Event event;
      while(1)
     {
       SDL_WaitEvent(&event);
        if (event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
      {
        int x,y;
        x = event.button.x ;
        y = event.button.y ;
        if(x>=200 && x<=250 && y>=400 && y<=450)
             {taille++;break;}
        else if(x>=250 && x<=450 && y>=400 && y<=450 && taille>3)
             {taille--;break;}
        else if(x>=300 && x<=500 && y>=550 && y<=600)
              {TTF_CloseFont(police);
               TTF_Quit();
               SDL_FreeSurface(texte);
               TTF_Quit();
               return taille;}
        }
      }
     }
}
       
      
        
       
       
    
     
