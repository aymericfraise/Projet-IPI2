
struct Liste;
typedef struct Liste Liste;
struct Composante;
struct Graphe;


struct Composante{
  int num;
  int col; // 0:R, 1:V, 2:B, 3:G, 4:M, 5:J
  int masse;
  int total_voisins;

  Liste** voisins;
  int* nb_voisins; // 0:R, 1:V, 2:B, 3:G, 4:M, 5:J
};
typedef struct Composante Composante;

struct Graphe{
  Composante** comps;
  int nb_comp;
  int* pris; /*pris[i]=1 si la composante i a été intégrée a la tache*/
};
typedef struct Graphe Graphe;

struct Liste {
    Composante* comp;
    struct Liste *suivant;
};

/**
  \fn graphe_init(int )
  \param  taille de la grille
  \return le graphe
**/
Graphe* graphe_init(int );

/**
  \fn mark_all_comp(Graphe*, char* , int* , int)
  \param  graphe pour save les composantes
  \param grille des couleur
  \param grille des composantes
  \param taille de la grille
**/
void mark_all_comp(Graphe*, char* , int* , int);

/**
  \fn trouve_voisins(Graphe* ,int *,int )
  \param  graphe des composantes
  \param grille des composantes
  \param taille de la grille
**/
void trouve_voisins(Graphe* ,int *,int );

/**
  \fn solveur(Graphe* , char* , int , int* , int)
  \param le graphe
  \param la solution
  \param le nb de coup deja jouer
  \param le max actuel
  \param la taille de la grille
**/
void solveur(Graphe* , char* , int , int* , int);

/**
  \fn freell(Liste *)
  \param la Liste a free
**/
void freell(Liste *);
