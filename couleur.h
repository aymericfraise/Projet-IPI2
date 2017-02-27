#include<time.h>
#include <stdbool.h>


/*definition de la structure de liste d'entier*/
typedef struct t_liste cell,*liste;
/*renvoie 1 si la liste est vide 0 sinon*/
int listevide(liste l);
/*ajoute l'element d a la liste l*/
liste makel(int d,liste l);
/*renvoie la tete de la liste*/
int pop(liste l);
/*renvoie la queue de la liste*/
liste sui(liste l);
/*libere la memore pour les liste*/
void freel(liste l);

/*donne a la case i de la grille g la valeur c*/
/*void change1(grille g,int i,char c);*/
/*renvoie la liste des position des cases appartenant a la composante connexe*/
liste composante(grille,liste,int);
/*donne au case de laliste l dans la grille g la valeur c*/
void changeall(grille g,liste l,char c);
/*renvoie 1 en cas de victoire 0 sinon*/
int win(grille,int);
