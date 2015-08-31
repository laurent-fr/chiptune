CC=g++
CFLAGS=-g -W -Wall -Werror -fexceptions -std=c++11 -pedantic -D_GNU_SOURCE -Iinclude

LDFLAGS= -lSDL2 -lSDL2_mixer -lm -lsndfile

playtune: build/main.o build/Song.o build/Track.o build/Note.o build/Instrument.o
	$(CC) -o playtune build/main.o build/Song.o build/Track.o build/Note.o build/Instrument.o $(LDFLAGS)

build/main.o: src/main.cpp
	$(CC) -c src/main.cpp -o build/main.o $(CFLAGS) 

build/Track.o: src/Track.cpp
	$(CC) -c src/Track.cpp -o build/Track.o $(CFLAGS)

build/Song.o: src/Song.cpp
	$(CC) -c src/Song.cpp -o build/Song.o $(CFLAGS)

build/Note.o: src/Note.cpp
	$(CC) -c src/Note.cpp -o build/Note.o $(CFLAGS)

build/Instrument.o: src/Instrument.cpp
	$(CC) -c src/Instrument.cpp -o build/Instrument.o $(CFLAGS)

clean:
	rm build/*.o
	rm playtune
