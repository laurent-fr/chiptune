#include "Track.h"
#include <stdio.h>
Track::Track()
{
    _length=0;
    _counter=0;
    //printf("New track \n");


}

Track::~Track()
{
    //dtor
}

Note Track::getNote() {
    return _notes.at(_counter);
}
