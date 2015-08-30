#include "Note.h"

Note::Note()
{
    //ctor
}

Note::Note(int tick,uint8_t note,uint8_t volume, int duration ) {

    _tick=tick;
    _note=note;
    _volume=volume;
    _duration=duration;

}

Note::~Note()
{
    //dtor
}

