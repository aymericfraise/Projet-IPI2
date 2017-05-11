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
SDL_Color couleurNoire = {0, 0, 0};
SDL_Color couleurBleu = {0, 0, 255};
SDL_Color couleurVert = {0, 100, 0};
SDL_Color couleurRouge = {255, 0, 0};
SDL_Color couleurJaune = {255,215,0};
SDL_Color couleurMarron = {139, 69, 19};
SDL_Color couleurGris = {139, 87, 66};

 

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


void affiche_SDL(grille g,int taille,SDL_Surface *ecran,int sz_rect,int coup,int mmax,int flag,int ww)
{
    SDL_Rect animRect;
    animRect.x = 0 ;
    animRect.y = 500 ;
    animRect.w = 500 ; 
    animRect.h = 200 ; 
    SDL_FillRect(ecran , &animRect , SDL_MapRGB(ecran->format , 255 ,255 ,255 ) );
   int i,ligne,colonne;
   char couleur;
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    char msg[100]="\n";
    sprintf(msg,"%d/%d",coup,mmax);
    police = TTF_OpenFont("2.ttf", 40);
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

/*la première initialisation*/
   if(flag==1)
  {
        police = TTF_OpenFont("2.ttf", 30);
        position.x = 10;
        position.y = 550;
        sprintf(msg,"mode de jouer:");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 10;
        position.y = 610;
        sprintf(msg,"facile");
        texte = TTF_RenderText_Blended(police, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 160;
        position.y = 610;
        sprintf(msg,"moyen");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 330;
        position.y = 610;
        sprintf(msg,"difficile");
        texte = TTF_RenderText_Blended(police, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
 }
     else if( flag==0 && ww==0)
 {
        SDL_Flip(ecran);
        position.x = 200;
        position.y = 600;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
 }
  else if(flag==0 && ww==1)
   {        
        police = TTF_OpenFont("fireworks.ttf", 100); 
        position.x = 50;
        position.y = 610;
        sprintf(msg,"y");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
         police = TTF_OpenFont("2.ttf", 30); 
        position.x = 170;
        position.y = 610;
        sprintf(msg,"GAGNEZ!");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        police = TTF_OpenFont("fireworks.ttf", 100); 
        position.x = 400;
        position.y = 610;
        sprintf(msg,"y");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);

   }
   if(coup==0)
  {
        SDL_FillRect(ecran , &animRect , SDL_MapRGB(ecran->format , 255 ,255 ,255 ) );
        police = TTF_OpenFont("2.ttf", 30); 
        position.x = 160;
        position.y = 600;
        sprintf(msg,"DOMMAGE");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        police = TTF_OpenFont("face.ttf", 100); 
        position.x = 30;
        position.y = 600;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */  
        position.x = 370;
        position.y = 600;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */        
        SDL_Flip(ecran);
  }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    TTF_Quit();
}





int saisir_taille(SDL_Surface *ecran)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   int taille=3;
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police = NULL;
    int continuer = 1;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
   /* police = TTF_OpenFont("angelina.ttf", 50);*/
    police = TTF_OpenFont(/*Quaterback Fight*/"1.ttf", 40);
    char msg[100]="\n";
   while (continuer)
    {
        police = TTF_OpenFont(/*Quaterback Fight*/"star.ttf", 40);
        sprintf(msg,"C");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x = 27;
        position.y = 100;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police, msg, couleurJaune);
        position.x = 27+50;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurMarron);
        position.x = 27+100;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police, msg, couleurVert);
        position.x = 27+150;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"R");
        texte = TTF_RenderText_Blended(police, msg, couleurBleu);
        position.x = 27+200;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"F");
        texte = TTF_RenderText_Blended(police, msg, couleurBleu);
        position.x = 27+250+20;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurVert);
        position.x = 27+20+300;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police, msg, couleurMarron);
        position.x = 27+20+350;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police, msg, couleurJaune);
        position.x = 27+20+400;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        sprintf(msg,"D");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        position.x = 27+20+450;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        police = TTF_OpenFont("face.ttf", 100);
        position.x = 215;
        position.y = 200;
        sprintf(msg,"T");
        texte = TTF_RenderText_Blended(police, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        police = TTF_OpenFont("block.ttf", 30);
        position.x = 10;
        position.y = 370;
        sprintf(msg,"T");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 10+40;
        sprintf(msg,"A");
        texte = TTF_RenderText_Blended(police, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */ 
        position.x=10+80;
        sprintf(msg,"I");
        texte = TTF_RenderText_Blended(police, msg, couleurGris);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x=10+120;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x=10+160;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police, msg, couleurBleu);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x=10+200;
        sprintf(msg,"E");
        texte = TTF_RenderText_Blended(police, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
        police = TTF_OpenFont("2.ttf", 35);
        position.x = 210;
        position.y = 450;
        sprintf(msg,"+ %d -",taille);
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
         SDL_Flip(ecran);
        police = TTF_OpenFont("ballon.ttf", 30);
        position.x = 300;
        position.y = 570;
        sprintf(msg,"COM");
        texte = TTF_RenderText_Blended(police, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 300+73;
        sprintf(msg,"MEN");
        texte = TTF_RenderText_Blended(police, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        position.x = 300+73+73;
        sprintf(msg,"CEZ");
        texte = TTF_RenderText_Blended(police, msg, couleurBleu);
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
        if(x>=210 && x<=250 && y>=450 && y<=485)
             {taille++;break;}
        else if(x>=260 && x<=450 && y>=450 && y<=485 && taille>3)
             {taille--;break;}
        else if(x>=300 && x<=560 && y>=570 && y<=600)
              {TTF_CloseFont(police);
               TTF_Quit();
               SDL_FreeSurface(texte);
               TTF_Quit();
               return taille;}
        }
      }
     }
           return taille;
}
       
      
        
       
       
    
     
