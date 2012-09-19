CC=cc
CFLAGS=-O

nyan: nyan.c nyan.h
	$(CC) $(CFLAGS) -o nyan nyan.c -lcurses -ltermcap
#	$(CC) $(CFLAGS) -o nyan nyan.c -lcurses

