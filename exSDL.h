// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
// px, py coordonnées haut, gauche du pixel

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

void affiche_SDL(grille g,int taille,SDL_Surface *ecran/*,int coup*/);
