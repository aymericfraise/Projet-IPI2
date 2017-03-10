#include <SDL/SDL.h>
#include "grille.h"
#include "couleur.h"
#include "exSDL.h"
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
