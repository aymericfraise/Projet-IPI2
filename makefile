CC=gcc
CFLAGS=-std=gnu89 -Wall -Wextra -g

all: prog tests_unitaires2 tests_unitaires


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:grille.h couleur.h couleur.c
	$(CC) $(CFLAGS) -c couleur.c

exSDL.o:grille.h  couleur.h 
	$(CC) $(CFLAGS) -c  exSDL.c
tests.o:grille.h tests.c couleur.h
	$(CC) $(CFLAGS) -c tests.c

tests_unitaires.o: tests_unitaires.c grille.h couleur.h
	$(CC) $(CFLAGS) -c tests_unitaires.c -lcunit

tests_unitaires2.o: tests_unitaires2.c grille.h couleur.h minunit.h
	$(CC) $(CFLAGS) -c tests_unitaires2.c


prog:exSDL.o grille.o couleur.o 
	$(CC) $(CFLAGS)    $^ -o $@ -lSDL

tests_unitaires: tests_unitaires.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

tests_unitaires2: tests_unitaires2.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm tests.o grille.o couleur.o tests_unitaires.o tests_unitaires2.o
