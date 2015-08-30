CC=g++
CGLAGS= -g -W -Wall -Werror -fexceptions -std=c++11 -pedantic -D_GNU_SOURCE

LDFLAGS= `sdl-config --libs` -lSDL2_mixer -lm -lsndfile

playtune: chiptune.o
	$(CC) -o playtune playtune.o $(LDFLAGS)

playtune.o: chiptune.c
	$(CC) -c playtune.c $(CFLAGS)
