CC=gcc
CFLAGS=-std=gnu89 -Wall -Wextra -g
OBJS = main.o exSDL.o tests.o grille.o couleur.o tests_unitaires.o tests_unitaires2.o

all: prog tests_unitaires2 tests_unitaires doxygen

#-------------------------------------------------------------------

grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:couleur.c grille.h couleur.h
	$(CC) $(CFLAGS) -c couleur.c

exSDL.o: exSDL.c exSDL.h grille.h couleur.h
	$(CC) $(CFLAGS) -c  exSDL.c

naif.o : naif.c grille.h couleur.h exSDL.h
	$(CC) $(CFLAGS) -c  naif.c

main.o : main.c grille.h couleur.h exSDL.h naif.h
	$(CC) $(CFLAGS) -c  main.c

tests_unitaires.o: tests_unitaires.c grille.h couleur.h
	$(CC) $(CFLAGS) -c tests_unitaires.c -lcunit

tests_unitaires2.o: tests_unitaires2.c grille.h couleur.h minunit.h
	$(CC) $(CFLAGS) -c tests_unitaires2.c

#-------------------------------------------------------------------

prog : main.o exSDL.o grille.o couleur.o naif.o
	$(CC) $(CFLAGS)    $^ -o $@ -lSDL

tests_unitaires: tests_unitaires.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

tests_unitaires2: tests_unitaires2.o grille.o couleur.o
	$(CC) $(CFLAGS) $^ -o $@

doxygen:
	doxygen doxygen.cfg

#-------------------------------------------------------------------

clean:
	rm $(OBJS)

purge:
	rm $(OBJS) prog tests_unitaires tests_unitaires2;\
	rm -rf doc
