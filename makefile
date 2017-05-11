CC=gcc
CFLAGS=-std=gnu89 -Wall -Wextra -g
OBJS = main.o exSDL.o grille.o couleur.o tests_unitaires.o naif.o

all: color-flood tests_unitaires doxygen

#-------------------------------------------------------------------

grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:couleur.c grille.h couleur.h
	$(CC) $(CFLAGS) -c couleur.c

exSDL.o: exSDL.c exSDL.h grille.h couleur.h
	$(CC) $(CFLAGS) -c  exSDL.c  -lSDL -lSDL_ttf -Wno-missing-field-initializers

naif.o : naif.c grille.h couleur.h exSDL.h
	$(CC) $(CFLAGS) -c  naif.c -lSDL  -lSDL_ttf

main.o : main.c grille.h couleur.h exSDL.h naif.h
	$(CC) $(CFLAGS) -c  main.c  -lSDL -lSDL_ttf -Wno-missing-field-initializers

tests_unitaires.o: tests_unitaires.c grille.h couleur.h
	$(CC) $(CFLAGS) -c tests_unitaires.c -lcunit -lSDL -lSDL_ttf

#-------------------------------------------------------------------

color-flood : main.o exSDL.o grille.o couleur.o naif.o
	$(CC) $(CFLAGS)    $^ -o $@ -lSDL -lSDL_ttf

tests_unitaires: tests_unitaires.o exSDL.o grille.o couleur.o naif.o
	$(CC) $(CFLAGS) $^ -o $@ -lSDL -lcunit -lSDL_ttf

doxygen:
	doxygen doxygen.cfg

#-------------------------------------------------------------------

clean:
	rm $(OBJS)

purge:
	rm $(OBJS) color-flood tests_unitaires;\
	rm -rf doc
