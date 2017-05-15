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
  \fn affiche_SDL(grille g,int taille,SDL_Surface *ecran,int sz_rect,int coup,int mmax,int flag,int ww);
  \param grille g représente la grille
  \param int taille représente la taille de grille
  \param SDL_Surface *ecran représente l'écran
  \param int sz_rect représente ma taille de rectangle
  \param int coup représente le coup restant
  \param int mmax représente le coup autorisé au tout début
  \param int flag représente si c'est la première fois qu'on lance le jeu
  \param int ww représente si le joueur gagne ou pas
  \brief Permet de réaliser tout les effet d'affichage pendant jouer
*/
void affiche_SDL(grille g,int taille,SDL_Surface *ecran,int sz_rect,int coup,int mmax,int flag,int ww);


/**
    \fn saisir_taille(SDL_Surface *ecran)
    \param SDL_Surface *ecran
    \return la taille
    \brief Permet de retourner la taille de grille que le joueur choisit et il peut réaliser les effetd de page d'acceuil
**/
int saisir_taille(SDL_Surface *ecran);
/**
    \fn set_sz_rect(int taille,int* width);
    \param int taille,int* width
    \return la taille de chaque case 
    \brief Permet de retourner la taille de chaque case à l'aide de taille et width du graphe
**/
int set_sz_rect(int taille,int* width);
/**
    \fn clik_change(SDL_Surface *ecran);
    \param SDL_Surface *ecran
    \return la couleur de la part que tu cliques 
    \brief Permet d'obtenir la couleur 
**/
Uint8* clik_change(SDL_Surface *ecran);
/**
    \fn  find_couleur(Uint8 * p);
    \param Uint8 * p
    \return la couleur qui correspond à la couleur que la paramètre p signifie
    \brief Permet d'obtenir la couleur sous la forme de caractère
**/
char find_couleur(Uint8 * p);
/**
    \fn  couleur_marche(int j[6],char couleur);
    \param int j[6],char couleur
    \return la valeur 1 ou la valeur 0
    \brief Permet de savoir si cette couleur marche ou pas dans ce cas
**/
int  couleur_marche(int j[6],char couleur);
/**
    \fn  mode_jouer(int coup);
    \param int coup
    \return la valeur de coup autorisé
    \brief Permet de retourner le coup choisit
**/
int mode_jouer(int coup);




