#ifndef NOTE_H
#define NOTE_H

#include <cstdint>

class Note
{
    public:

        int _tick;
        uint8_t _note;
        uint8_t _volume;
        int _duration;

        Note();
        Note(int tick,uint8_t note,uint8_t volume, int duration );
        virtual ~Note();

    protected:
    private:
};

#endif // NOTE_H
