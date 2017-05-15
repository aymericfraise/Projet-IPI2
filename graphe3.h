
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

Graphe* graphe_init(int );
void mark_all_comp(Graphe*, char* , int* , int);
void trouve_voisins(Graphe* ,int *,int );
void solveur(Graphe* , char* , int , int* , int);
void freell(Liste *);
