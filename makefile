CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -g
all:prog


grille.o:grille.c grille.h
	$(CC) $(CFLAGS) -c grille.c

test_grille.o:grille.h test_grille.c
	$(CC) $(CFLAGS) -c test_grille.c

prog:test_unitaires.o grille.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm test_grille.o grille.o
