#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "graphe3.h"

/* Header ############################################# */


/* Utilitaire ###########################################*/

char random_letter(){
    int i=random()%6+1;
    char couleur;
    switch(i){
        case 1:couleur='B';break;
        case 2:couleur='V';break;
        case 3:couleur='R';break;
        case 4:couleur='J';break;
        case 5:couleur='M';break;
        case 6:couleur='G';break;
        default:break;
    }
    return couleur;
}

char* grille_init_random(int taille){
  char* g = malloc(taille*taille*sizeof(char));
  int i;
  for(i=0; i<taille*taille; i++){
    g[i] = random_letter();
  }
  return g;
}

void print_char_grille(char* g, int taille){
  for(int i=0;i<taille*taille;i++){
    printf("%2c ",g[i]);
    if(i%taille==taille-1)printf("\n");
  }
  printf("\n");
}

void print_int_grille(int* g, int taille){
  for(int i=0;i<taille*taille;i++){
    printf("%2d ",g[i]);
    if(i%taille==taille-1)printf("\n");
  }
  printf("\n");
}

/* renvoit l'entier correspondant a la couleur donnée */
int colToInt(char col){
  switch(col){
    case 'R' : return 0; break;
    case 'V' : return 1; break;
    case 'B' : return 2; break;
    case 'G' : return 3; break;
    case 'M' : return 4; break;
    case 'J' : return 5; break;
    default :
      printf("couleur invalide %d\n",col);
      exit(1);
      break;
  }
}

/* Struct composante et graphe ############################################*/



/*Fonctions de liste ##############################################*/

Liste* initListeVide(){
  return NULL;
}

int estVide(Liste* l){
  return (l==NULL);
}

Liste* constructeur2(Composante* i, Liste* l){
    Liste* liste = malloc(sizeof(struct Liste));
    liste->comp = i;
    liste->suivant = l;

    return liste;
}

int longueurListe(Liste* l){
  int longueur = 0;
  Liste* l2 = l;
  while(!estVide(l2)){
    longueur ++;
    l2 = l2->suivant;
  }
  return longueur;
}

void affiche(Liste* l){
  Liste* l2 = l;
  while(!estVide(l2)){
    printf("%d ",l2->comp->num);
    l2 = l2->suivant;
  }
  printf("\n");
}

int rechercheElement(int x, Liste* l){
  Liste* l2 = l;
  int trouve = 0;
  while(!estVide(l2) && !trouve){
    if(l2->comp->num == x) trouve = 1;
    l2 = l2->suivant;
  }
  return(trouve);
}

void supprimeElement(int x, Liste* *l){
  Liste* actuel;
  Liste* precedent;
  precedent = NULL;
  actuel = *l;
  int trouve = 0;
  while(!estVide(actuel) && !trouve)
  {
    if (actuel->comp->num == x) {
      trouve = 1;
      if (precedent == NULL)
        /* si c'est le premier element, on change l'adresse du début */
        *l = actuel->suivant;
      else
        /* sinon, on "dépasse" la case de l'élément et on lie
        direct celle d'apres */
        precedent->suivant = actuel->suivant;
    }
    else{
      precedent = actuel;
      actuel = actuel->suivant;
    }
  }
  if(actuel != *l) free(actuel);
}

/*###############################################*/

//affiche les voisins de la tache
void print_graphe(Graphe* g){
  Composante* tache = g->comps[0];
  Liste* l2;

  printf("voisins tache : \n");
  for(int i=0; i<6; i++){
    printf("c%d(%d): ",i,tache->nb_voisins[i]);
    //affiche(tache->voisins[i]);
    l2 = tache->voisins[i];
    while(!estVide(l2)){
      //if(!g->pris[l2->comp->num])
      printf("%d ",l2->comp->num);
      l2 = l2->suivant;
    }
    printf("\n");
  }
  printf("\n");
}

/* CREATION DU GRAPHE ######################################################*/

Composante* comp_init(Graphe* g, int *g_comp, int col, int taille, int masse){
  Composante* comp = malloc(sizeof(struct Composante));
  comp->num = g->nb_comp;
  comp->col = col;
  comp->masse=masse;
  g->comps[g->nb_comp] = comp;
  g->nb_comp ++;

  comp->voisins = malloc(6*sizeof(Liste*));
  for(int i=0; i<6; i++){
    comp->voisins[i] = initListeVide();
  }
  comp->nb_voisins = calloc(6,sizeof(int));
  return comp;
}

Graphe* graphe_init(int taille){
  Graphe* g = malloc(sizeof(Graphe));
  g->comps = malloc(taille*taille*sizeof(Composante*));
  g->nb_comp=0;
  g->pris = calloc(sizeof(int),taille*taille);
  g->pris[0]=1;
  return g;
}

/* marque tous les pixels de la composante du pixel i par propagation
et initialise la composante
*/
void mark_comp(Graphe* g, char* g_col, int* g_comp, int col, int i, int comp_nb, int taille, int* masse){
  if(colToInt(g_col[i]) == col && g_comp[i]==-1){
    g_comp[i]=comp_nb;
    (*masse)++;
    //pas premiere ligne
    if(i>taille)
      mark_comp(g, g_col, g_comp, col, i-taille, comp_nb, taille, masse);
    //pas derniere ligne
    if(i<taille*(taille-1))
      mark_comp(g, g_col, g_comp, col, i+taille, comp_nb, taille, masse);
    //pas premiere colonne
    if(i%taille!=0)
      mark_comp(g, g_col, g_comp, col, i-1, comp_nb, taille, masse);
    //pas derniere colonne
    if(i%taille!=taille-1)
      mark_comp(g, g_col, g_comp, col, i+1, comp_nb, taille, masse);
  }
}

/* crée g_comp, le tableau associant à un pixel une composante
  (g_comp[i] = numero de composante du pixel i
*/
void mark_all_comp(Graphe* g, char* g_col, int* g_comp, int taille){
  /* on marque tous les pixels comme non traités */
  for(int i=0; i<taille*taille;i++){
    g_comp[i]=-1;
  }

  /*pour chaque pixel de la grille (g_col), si on a pas déjà déterminé
  sa composante, on lance une propagation pour la déterminer */
  int masse;
  for(int i=0;i<taille*taille;i++){
    if(g_comp[i]==-1){
      masse=0;
      mark_comp(g, g_col, g_comp, colToInt(g_col[i]), i, g->nb_comp, taille, &masse);
      comp_init(g, g_comp, colToInt(g_col[i]), taille, masse);
    }
  }
}

/* ajoute c2 dans les voisins c1 */
void ajoute_voisins(Graphe* g, int num_c1, int num_c2){
  Composante* c1 = g->comps[num_c1];
  Composante* c2 = g->comps[num_c2];
  c1->voisins[c2->col] = constructeur2(c2,c1->voisins[c2->col]);
  c1->nb_voisins[c2->col]++;
}

/* determine les voisins de chaque composante */
void trouve_voisins(Graphe* g,int *g_comp,int taille){
  /*Pour chaque composante, on regarde chaque pixel de la grille des composantes
    Pour chaque pixel on regarde ses voisins
    Si il y a un voisin de composante differente, on ajoute cette composante dans
    les voisins de la composante courante
  */
  int fait[taille*taille]; // fait[i]=1 si la composante i a été ajoutée dans les voisins de la composante courante
  for (size_t i = 0; i < taille*taille; i++) {
    for (size_t j = 0; j < taille*taille; j++) {
      fait[j]=0;
    }
    fait[i]=1;
    for (size_t j = 0; j < taille*taille; j++) {
      if (g_comp[j]==i) {
          if(j>taille-1 && !fait[g_comp[j-taille]]) {
            ajoute_voisins(g,i,g_comp[j-taille]);
            fait[g_comp[j-taille]]=1;
          }
          if(j<taille*(taille-1) && !fait[g_comp[j+taille]]) {
            ajoute_voisins(g,i,g_comp[j+taille]);
            fait[g_comp[j+taille]]=1;
          }
          if(j%taille!=0 && !fait[g_comp[j-1]]) {
            ajoute_voisins(g,i,g_comp[j-1]);
            fait[g_comp[j-1]]=1;
          }
          if(j%taille!=(taille-1) && !fait[g_comp[j+1]]) {
            ajoute_voisins(g,i,g_comp[j+1]);
            fait[g_comp[j+1]]=1;
          }
      }
    }
  }
}

/* solveur ############################################*/

void modifie_graphe(Graphe* g, int col, int* mem){
  Composante* tache = g->comps[0];
  Composante* voisin;
  Composante* voisin2;
  Liste* liste_voisins = tache->voisins[col];
  Liste* liste_voisin2;
  int nb_comp = g->nb_comp;

  /* on itère sur tous les voisins de couleur col de la tache */
  while(!estVide(liste_voisins)){ //tant qu'il reste des voisins de la bonne couleur
    voisin = liste_voisins->comp; //on regarde la tete de liste des voisins de la bonne couleur

    /* on ajoute aux voisins de la tache chaque voisin de la composante voisine de la tache
    qui ne fait pas déjà parti de la tache */
    for(int i=0; i<6; i++){ //pour chaque couleur
      liste_voisin2 = voisin->voisins[i]; //on regarde la tete de liste des voisins de couleur i du voisin
      while(!estVide(liste_voisin2)){ //on itere sur cette liste
        voisin2 = liste_voisin2->comp;
        /*si le voisin au deuxieme degré n'est ni dans la tache ni voisine de la tache,
        on l'ajoute aux voisins de la tache*/
        if(!g->pris[voisin2->num] && !rechercheElement(voisin2->num, tache->voisins[i])){
          mem[voisin2->num]=1; /* on retient qu'on a ajouté la composante */
          tache->voisins[i] = constructeur2(voisin2, tache->voisins[i]);
          tache->nb_voisins[i] ++;
        }
        liste_voisin2 = liste_voisin2->suivant;
      }
    }

    /* on assimile le voisin a la tache et on le supprime des voisins de la tache */
    liste_voisins = liste_voisins->suivant;

    g->pris[voisin->num]=1;
    mem[voisin->num]=-1;
    //printf("suppression %d\n",voisin->num);
    //printf("avant (%d): ",longueurListe(tache->voisins[col]));
    //affiche(tache->voisins[col]);
    supprimeElement(voisin->num,&(tache->voisins[col]));
    //printf("apres (%d): ",longueurListe(tache->voisins[col]));
    //affiche(tache->voisins[col]);
    tache->nb_voisins[col] --;

  }
}

void undo(Graphe* g, int* mem, int taille){
  Composante* tache = g->comps[0];
  Composante* voisin;
  int col;
  for(int i=0;i<g->nb_comp;i++){
    if(mem[i]==-1){
      voisin = g->comps[i];
      col = voisin->col;
      tache->voisins[col]=constructeur2(voisin,tache->voisins[col]);
      tache->nb_voisins[col]++;
      g->pris[i]=0;
      mem[i]=0;
    }
    else if(mem[i]==1){
      voisin = g->comps[i];
      col = voisin->col;
      supprimeElement(voisin->num,&(tache->voisins[col]));
      tache->nb_voisins[col]--;
      mem[i]=0;
    }
  }
}

int winn(Graphe* g){
  int* nb = g->comps[0]->nb_voisins;
  return nb[0]+nb[1]+nb[2]+nb[3]+nb[4]+nb[5] == 0;
}

void solveur(Graphe* g, char* solution, int nb_coups, int* max, int taille){
  int* hors_tache = calloc(sizeof(int),6);
  int nb_hors_tache = 0;
  for(int i=0;i<g->nb_comp;i++){
    if(!g->pris[i]){
      if(hors_tache[g->comps[i]->col]==0) nb_hors_tache++;
      hors_tache[g->comps[i]->col] ++;
    }
  }
  free(hors_tache);

  if(nb_coups + nb_hors_tache < *max){
    if(winn(g)){
      *max=nb_coups;
      solution[nb_coups]='\0';
      printf("solution trouvée en %3d coups : %s\n", nb_coups, solution);
    }

    int* mem = calloc(g->nb_comp,sizeof(int));
    char couleurs[6] = {'R','V','B','G','M','J'};

    for(int col=0; col<6; col++){
      if(g->comps[0]->nb_voisins[col] > 0){
        modifie_graphe(g, col, mem);
        solution[nb_coups]=couleurs[col];
        solveur(g, solution, nb_coups+1, max, taille);
        undo(g,mem,taille);
      }
    }
    free(mem);
  }
}

void freell(Liste *l){
  if (!estVide(l)) {
    freell(l->suivant);
    free(l);
  }
}
/*############################################*/

/*int main(){
  int taille=10;
  srand(time(NULL));
  char* g_col = grille_init_random(taille); //grille des couleurs des pixels
  int* g_comp = malloc(sizeof(int)*taille*taille); //grille des composantes des pixels

  //debug
  print_char_grille(g_col,taille);

  /*initialise le graphe*/
/*  Graphe* g = graphe_init(taille);

  /*initialise les composantes*/
/*  mark_all_comp(g, g_col,g_comp,taille);

  //debug
  print_int_grille(g_comp, taille);

  /*trouve les voisins de chaque composante*/
/*  trouve_voisins(g, g_comp, taille);

  char* solution = calloc(g->nb_comp,sizeof(char));
  int max = g->nb_comp;
  solveur(g, solution, 0, &max, taille);

  free(g_col);
  free(g_comp);
	free(solution);
  for (size_t i = 0; i < g->nb_comp; i++) {
    for (size_t j = 0; j < 6; j++) {
      freell(g->comps[i]->voisins[j]);
    }
    free(g->comps[i]->voisins);
    free(g->comps[i]->nb_voisins);
    free(g->comps[i]);
  }

  free(g->comps);
	free(g->pris);
	free(g);
  return 0;
}*/
