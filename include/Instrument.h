#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <math.h>
#include <stdlib.h>

#include "Note.h"

#include "config.h"

#define A 1.059463094359 // 2^(1/12)

typedef enum waveforms_e {
            square,
            triangle,
            saw,
            sinus,
            noise
        } wafeforms_t ;

class Instrument
{
    public:

        // instrument definition
        waveforms_e _waveform=square;
        float _duty_cycle=0.5;
        int _envelope_a=255;
        int _envelope_d=0;
        int _envelope_s=255;
        int _envelope_r=255;



        // instrument playing variables
        int _note;
        float _frequency;
        int _duration;
        int _duration_left;
        int _volume;
        float _envelope_volume=0;
        float _phase=0;

        enum adsr_mode_e { mode_a, mode_d, mode_s, mode_r};
        adsr_mode_e _adsr_mode;

        Instrument();
        virtual ~Instrument();

        void startNote(Note const &note);
        float play();

    protected:
    private:

        float getFrequency(int n);
        float getEnvelope();

        float playSin();
        float playSaw();
        float playTriangle();
        float playSquare();
        float playNoise();



};

#endif // INSTRUMENT_H
