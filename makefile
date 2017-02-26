CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c
	
test_unitaires.o:grille.h test_unitaires.c couleur.h
	$(CC) $(CFLAGS) -c test_unitaires.c

prog:test_unitaires.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm test_unitaires.o grille.o couleur.o
