PKGS=sdl2
CFLAGS=-Wall -ggdb -std=c11 -pedantic `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)`

chess: main.c
	$(CC) $(CFLAGS) -o chess main.c $(LIBS)
