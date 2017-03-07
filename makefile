CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c

play.o:grille.h play.c couleur.h
	$(CC) $(CFLAGS) -c play.c

prog:play.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm test_unitaires.o grille.o couleur.o
