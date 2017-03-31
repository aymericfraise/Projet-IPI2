/**
 \fn drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b)
 \param SDL_Surface*ecran représente l'écran
 \param int px,int py représentent les coordonnées de l'écran
 \param int size représente que le rectangle est composé de combien de pixel
 \param int r,int g,int b:ce sont les valeurs e RGB de couleur
*/



/*const SDL_Color RGB_Black  = { 0, 0, 0 };  
const SDL_Color RGB_BLEU   = { 0, 0, 255 }; 
const SDL_Color RGB_VERT   = { 0, 100, 0 };  
const SDL_Color RGB_ROUGE  = {255, 0, 0 };   
const SDL_Color RGB_JAUNE  = {255, 185, 15 };  
const SDL_Color RGB_MARRON = {139, 69, 19 };  
const SDL_Color RGB_GRIS   = {139, 87, 66 };*/

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
/**
\fn void fillScreen(SDL_Surface *ecran, int r, int g, int b)
\param SDL_Surface*ecran représente l'écran
\param int r,int g,int b:ce sont les valeurs e RGB de couleur
*/
void fillScreen(SDL_Surface *ecran, int r, int g, int b);

/**
 \fn upi(char c,int i[])
 \param couleur jouable a ajouter
 \param tableau a metre a jour
*/
void upi(char c,int i[]);

/**
 \fn jouable(grille g,liste l,int i[6],int taille)
 \param la grille de jeu
 \param la liste de la composante
 \param le tableau a metre a jour
 \param la taille
*/
void jouable(grille g,liste l,int i[],int taille);

/**
 \fn printjouable(int j[6])
 \param le tableau des couleur jouables
*/
void printjouable(int j[]);
/** 
  \fn void affiche_SDL(grille g,int taille,SDL_Surface *ecran)
  \param grille g représente la grille
  \param int taille représente la taille de grille
  \param SDL_Surface *ecran représente l'écran
  \param int sz_rect représente ma taille de rectangle
*/
void affiche_SDL(grille g,int taille,SDL_Surface *ecran,int sz_rect);
