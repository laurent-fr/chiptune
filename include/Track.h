#ifndef TRACK_H
#define TRACK_H

#include <vector>

#include "Note.h"
#include "Instrument.h"

using namespace std;

class Track
{
    public:
        int _length;
        int _counter;
        Instrument _instrument;

        vector<Note> _notes;

        Track();
        virtual ~Track();

        Note getNote();

    protected:
    private:



};

#endif // TRACK_H
