CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c

test_grille.o:grille.h test_grille.c couleur.h
	$(CC) $(CFLAGS) -c test_grille.c

prog:test_grille.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm test_grille.o grille.o couleur.o
