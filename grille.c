#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct Case
{
   char couleur;
   int dedant;
}*grille,Case;   


grille Grille(int taille)
{
        grille ret=NULL;
        ret=malloc(taille*taille*sizeof(Case));	
        return ret;
}


void Liberation(grille a)
{
    free(a);
}

char constructeur()
{
    int i=random()%6+1;     
    char couleur;
    switch(i)
   {
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
 



void init_grille(grille a,int taille)
{
     int i=0;
     for(i=0;i<taille*taille;i++)
     {
         a[i].couleur=constructeur();
     }
}


void cree_fichier_de_couleur(int taille)
{
   FILE *fp=fopen("couleur.dat","w+");
   int i;
   for(i=0;i<taille*taille;i++)
   {
     fputc(constructeur(),fp);
   }
   fclose(fp);
}


void init_grille_fichier(grille a,FILE *fp,int taille)
{
     int i=0;
     for(i=0;i<taille*taille;i++)
     {
         a[i].couleur=fgetc(fp);
     }
     fclose(fp); 
}




int main()
{
    int taille;
    int i;
    FILE* fp=fopen("couleur.dat","r");
    printf("Donnez la taille de grille,s'il vous plaît:");
    scanf("%d",&taille);
    grille g=Grille(taille);
    /*************************************************/
    printf("ici,c'est le résultat d'initialisation à partir de valeurs aléatoires:\n");
    init_grille(g,taille);
    for(i=0;i<taille*taille;i++)
    {
       printf("%c ",g[i].couleur);
       if(i%taille==taille-1)
       printf("\n");
    }   

     /******************************************************************/
       printf("ici,c'est le résultat d'initialisation à partir de valeurs contenue dans un fichier:\n");
        cree_fichier_de_couleur(taille);
        init_grille_fichier(g,fp,taille);
        for(i=0;i<taille*taille;i++)
       {
       printf("%c ",g[i].couleur);
       if(i%taille==taille-1)
       printf("\n");
       } 

     Liberation(g);
     
     return 0;
}


     
         






