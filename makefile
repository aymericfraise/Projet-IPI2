CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g 
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c

exSDL.o:grille.h  couleur.h 
	$(CC) $(CFLAGS) -c  exSDL.c

prog:exSDL.o grille.o couleur.o 
	$(CC) $(CFLAGS)    $^ -o $@ -lSDL

clean:
	rm test_unitaires.o grille.o couleur.o
