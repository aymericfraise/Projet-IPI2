CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

couleur.o:couleur.c grille.h couleur.h
	$(CC) $(CFLAGS) -c couleur.c

exSDL.o: exSDL.c exSDL.h
		$(CC) $(CFLAGS) -c  exSDL.c

main.o : main.c grille.h couleur.h exSDL.h
		$(CC) $(CFLAGS) -c  main.c

prog : main.o exSDL.o grille.o couleur.o
	$(CC) $(CFLAGS)    $^ -o $@ -lSDL

clean:
	rm test_unitaires.o grille.o couleur.o
