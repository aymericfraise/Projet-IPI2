CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g

all: prog tests_unitaires


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c

tests.o:grille.h tests.c couleur.h
	$(CC) $(CFLAGS) -c tests.c

tests_unitaires.o: tests_unitaires.c grille.h couleur.h
	$(CC) $(CFLAGS) -c tests_unitaires.c

prog:tests.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

tests_unitaires: tests_unitaires.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm tests.o grille.o couleur.o tests_unitaires.o
