CC=cc
CFLAGS=-O0 -g

nyan: nyan.c nyan.h
	$(CC) $(CFLAGS) -o nyan nyan.c -lcurses -ltermcap

clean:
	rm -f nyan

