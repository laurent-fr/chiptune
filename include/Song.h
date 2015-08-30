#ifndef SONG_H
#define SONG_H

#include <map>
#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <sndfile.hh>

#include "config.h"
#include "Instrument.h"
#include "Track.h"
#include "Note.h"

using namespace std;

class Song
{
    public:

        map<int,Instrument> _instruments;
        map<int,Track> _tracks;

        Mix_Chunk _sample;

        Song();
        virtual ~Song();

        int load(string const &filename);
        void infos();
        void save(char *filename);

        void prepare();
        void play();

    protected:
    private:

        int _ticks_per_second = 168;
        int _sample_rate = SAMPLE_RATE;
        int _sample_size =0;

};

#endif // SONG_H
