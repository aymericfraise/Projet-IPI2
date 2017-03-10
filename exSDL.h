// px, py coordonnées haut, gauche de la texture
void drawTexture(SDL_Surface *ecran, int px, int py, SDL_Surface *ima);
// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
// px, py coordonnées haut, gauche du pixel
void drawPixel(SDL_Surface *ecran, int px, int py, int r, int g, int b);

void fillScreen(SDL_Surface *ecran, int r, int g, int b);

void upi(char c,int i[]);

void jouable(grille g,liste l,int i[],int taille);

void printjouable(int j[]);

void affiche_SDL(grille g,int taille,SDL_Surface *ecran/*,int coup*/);
