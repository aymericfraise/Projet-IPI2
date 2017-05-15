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
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *police1 = TTF_OpenFont("2.ttf", 30);;
    TTF_Font *police2 = TTF_OpenFont("2.ttf", 40);;
    TTF_Font *police3 = TTF_OpenFont("fireworks.ttf", 100); 
    TTF_Font *police4 = TTF_OpenFont("face.ttf", 100);
    char msg[100]="\n";
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
        position.x = 10;
        position.y = 550;
        sprintf(msg,"mode de jouer:");
        texte = TTF_RenderText_Blended(police1, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        position.x = 10;
        position.y = 610;
        sprintf(msg,"facile");
        texte = TTF_RenderText_Blended(police1, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        position.x = 160;
        position.y = 610;
        sprintf(msg,"moyen");
        texte = TTF_RenderText_Blended(police1, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        position.x = 330;
        position.y = 610;
        sprintf(msg,"difficile");
        texte = TTF_RenderText_Blended(police1, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
 }
     else if( flag==0 && ww==0)
 {
        sprintf(msg,"%d/%d",coup,mmax);
        texte = TTF_RenderText_Blended(police2, msg, couleurNoire);
        position.x = 200;
        position.y = 600;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
 }
  else if(flag==0 && ww==1)
   {        
        position.x = 50;
        position.y = 610;
        sprintf(msg,"y");
        texte = TTF_RenderText_Blended(police3, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 400;
        position.y = 610;
        sprintf(msg,"y");
        texte = TTF_RenderText_Blended(police3, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 170;
        position.y = 610;
        sprintf(msg,"GAGNEZ!");
        texte = TTF_RenderText_Blended(police1, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
 

   }
   if(coup==0)
  {
        SDL_FillRect(ecran , &animRect , SDL_MapRGB(ecran->format , 255 ,255 ,255 ) );
        position.x = 160;
        position.y = 600;
        sprintf(msg,"DOMMAGE");
        texte = TTF_RenderText_Blended(police1, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte); 
        position.x = 30;
        position.y = 600;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police4, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);  
        position.x = 370;
        position.y = 600;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police4, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);        
        SDL_Flip(ecran);
  }
    TTF_CloseFont(police1);
    TTF_CloseFont(police2);
    TTF_CloseFont(police3);
    TTF_CloseFont(police4);
    TTF_Quit();
    TTF_Quit();
}





int saisir_taille(SDL_Surface *ecran)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   int taille=3;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Surface *texte = NULL;
    SDL_Rect position;
    TTF_Font *police1 = TTF_OpenFont("star.ttf", 40); 
    TTF_Font *police2 = TTF_OpenFont("face.ttf", 100);
    TTF_Font *police3 = TTF_OpenFont("block.ttf", 30);
    TTF_Font *police4 = TTF_OpenFont("ballon.ttf", 30);
    TTF_Font *police5 = TTF_OpenFont("2.ttf", 35);
    char msg[100]="\n";
    int continuer = 1;
        while(continuer==1)
      {
        sprintf(msg,"C");
        texte = TTF_RenderText_Blended(police1, msg, couleurRouge);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x = 27;
        position.y = 100;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police1, msg, couleurJaune);
        position.x = 27+50;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police1, msg, couleurMarron);
        position.x = 27+100;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police1, msg, couleurVert);
        position.x = 27+150;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        sprintf(msg,"R");
        texte = TTF_RenderText_Blended(police1, msg, couleurBleu);
        position.x = 27+200;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        sprintf(msg,"F");
        texte = TTF_RenderText_Blended(police1, msg, couleurBleu);
        position.x = 27+250+20;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police1, msg, couleurVert);
        position.x = 27+20+300;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police1, msg, couleurMarron);
        position.x = 27+20+350;
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        sprintf(msg,"O");
        texte = TTF_RenderText_Blended(police1, msg, couleurJaune);
        position.x = 27+20+400;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        sprintf(msg,"D");
        texte = TTF_RenderText_Blended(police1, msg, couleurRouge);
        position.x = 27+20+450;
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
        position.x = 215;
        position.y = 200;
        sprintf(msg,"T");
        texte = TTF_RenderText_Blended(police2, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
        position.x = 10;
        position.y = 370;
        sprintf(msg,"T");
        texte = TTF_RenderText_Blended(police3, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 10+40;
        sprintf(msg,"A");
        texte = TTF_RenderText_Blended(police3, msg, couleurJaune);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte); 
        position.x=10+80;
        sprintf(msg,"I");
        texte = TTF_RenderText_Blended(police3, msg, couleurGris);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x=10+120;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police3, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        position.x=10+160;
        sprintf(msg,"L");
        texte = TTF_RenderText_Blended(police3, msg, couleurBleu);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        position.x=10+200;
        sprintf(msg,"E");
        texte = TTF_RenderText_Blended(police3, msg, couleurNoire);
        SDL_BlitSurface(texte, NULL, ecran, &position); 
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
        position.x = 300;
        position.y = 570;
        sprintf(msg,"COM");
        texte = TTF_RenderText_Blended(police4, msg, couleurVert);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 300+73;
        sprintf(msg,"MEN");
        texte = TTF_RenderText_Blended(police4, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        position.x = 300+73+73;
        sprintf(msg,"CEZ");
        texte = TTF_RenderText_Blended(police4, msg, couleurBleu);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
        SDL_Flip(ecran);
        position.x = 210;
        position.y = 450;
        sprintf(msg,"+ %d -",taille);
        texte = TTF_RenderText_Blended(police5, msg, couleurRouge);
        SDL_BlitSurface(texte, NULL, ecran, &position);
        SDL_FreeSurface(texte);
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
              {
               TTF_CloseFont(police1);
               TTF_CloseFont(police2);
               TTF_CloseFont(police3);
               TTF_CloseFont(police4);
               TTF_CloseFont(police5);
               TTF_Quit();
               return taille;
               }
        }
      }
    }

               TTF_CloseFont(police1);
               TTF_CloseFont(police2);
               TTF_CloseFont(police3);
               TTF_CloseFont(police4);
               TTF_CloseFont(police5);
               TTF_Quit();
               return taille;
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


int  couleur_marche(int j[6],char couleur)
{
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

int mode_jouer(int coup)
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
     
    
     
