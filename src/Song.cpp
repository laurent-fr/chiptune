#include "Song.h"

Song::Song()
{
    _sample_size=0;
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
            printf("SDL_Init: %s\n", SDL_GetError());
            exit(1);
    }

    int flags=0;
    Mix_Init(flags);

}

Song::~Song()
{
    //dtor
}

int Song::load(string const &filename) {

    int tick,duration;
    uint8_t track,note,volume;
    char *buffer = new char[8];

    // TEMP castlevania.tune
   /* _ticks_per_second=406;
    _tracks[2]._instrument._envelope_a=255;
    _tracks[2]._instrument._envelope_d=50;
    _tracks[2]._instrument._envelope_s=120;
    _tracks[2]._instrument._envelope_r=10;

    _tracks[3]._instrument._envelope_a=255;
    _tracks[3]._instrument._envelope_d=80;
    _tracks[3]._instrument._envelope_s=120;
    _tracks[3]._instrument._envelope_r=10;

    _tracks[5]._instrument._envelope_a=255;
    _tracks[5]._instrument._envelope_d=80;
    _tracks[5]._instrument._envelope_s=120;
    _tracks[5]._instrument._envelope_r=10;


    _tracks[6]._instrument._envelope_a=255;
    _tracks[6]._instrument._envelope_d=80;
    _tracks[6]._instrument._envelope_s=120;
    _tracks[6]._instrument._envelope_r=250;

    _tracks[4]._instrument._waveform = triangle;

    _tracks[7]._instrument._waveform = noise;
    _tracks[7]._instrument._envelope_d=50;
    _tracks[7]._instrument._envelope_s=0;*/

    // TEMP, mario.tune
    _tracks[2]._instrument._envelope_a=255;
    _tracks[2]._instrument._envelope_d=100;
    _tracks[2]._instrument._envelope_s=120;
    _tracks[2]._instrument._envelope_r=10;

    _tracks[3]._instrument._envelope_a=255;
    _tracks[3]._instrument._envelope_d=50;
    _tracks[3]._instrument._envelope_s=120;
    _tracks[3]._instrument._envelope_r=10;


    _tracks[4]._instrument._waveform = sinus;
    _tracks[4]._instrument._envelope_a=200;
    _tracks[4]._instrument._envelope_d=50;
    _tracks[4]._instrument._envelope_s=200;
    _tracks[4]._instrument._envelope_r=255;

    _tracks[5]._instrument._waveform = noise;
    _tracks[5]._instrument._envelope_d=50;
    _tracks[5]._instrument._envelope_s=0;

    ifstream file(filename,std::ios::binary);

    while (!file.eof()) {

        file.read(buffer,8);
        tick=(unsigned int)((uint8_t)buffer[0])*256+(uint8_t)buffer[1];
        tick*= _sample_rate/_ticks_per_second;
        track=buffer[2];
        note=buffer[3];
        volume=buffer[4];
        duration=(int)((uint8_t)buffer[5])*256+(uint8_t)buffer[6];
        duration*= _sample_rate/_ticks_per_second;

        if ((tick+duration)>_sample_size)
            _sample_size=tick+duration;

        _tracks[track]._notes.push_back( Note(tick,note,volume,duration) );
        _tracks[track]._length ++;

    }

    return 0;
}


void Song::infos() {

    for(auto kv : _tracks ) {
        Track track=kv.second;
        printf("Track %d, %d notes\n",kv.first,track._length);
    }

}

void Song::save(char *filename) {

    SndfileHandle file = SndfileHandle (filename, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, CHANNELS, SAMPLE_RATE) ;

    file.write ( (Sint16 *)_sample.abuf, _sample.alen) ;

}




void Song::prepare() {

    _sample.abuf=(Uint8 *)malloc(sizeof(Sint16)*_sample_size);
    _sample.alen=_sample_size*sizeof(Sint16);
    _sample.volume=128;


    for(int tick=0;tick<_sample_size;tick++) {

        Sint16 *data = (((Sint16 *)_sample.abuf)+tick);
        float output=0;

        for(auto& kv: _tracks) {

               // if (kv.first!=6) continue;

            Track& track = kv.second;
            if (track._counter >= track._length) {  continue; }

            Note note = track.getNote();

            if (tick>=note._tick) { //printf("tick=%d\n",tick);
                    track._instrument.startNote(note);
                    track._counter ++;

            }

            output+=track._instrument.play();

        }
        *data=(Sint16)(output);

    }


}

void Song::play() {

	Mix_OpenAudio(SAMPLE_RATE,FORMAT,CHANNELS,CHUNKSIZE);
	Mix_PlayChannel(0,&_sample,1);
	while(Mix_Playing(0));
	Mix_Quit();

}
