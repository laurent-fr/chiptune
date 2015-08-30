#include "Instrument.h"
#include<stdio.h>
Instrument::Instrument()
{
    //printf("New instrument \n");
}

Instrument::~Instrument()
{
    //dtor
}

void Instrument::startNote(Note const &note) {

    _note = note._note;
    _volume = note._volume;
    _duration = note._duration;
    _duration_left = note._duration;

    _frequency = getFrequency(note._note);

    _adsr_mode = mode_a;

}


float Instrument::getFrequency(int n) {

    float f = 440. * pow( A,n-69);
	if (f<=0) return 0;
	return f;

}

float Instrument::getEnvelope() {

    if (_duration_left<=0) _adsr_mode=mode_r;

    switch(_adsr_mode) {

        case mode_a:
            _envelope_volume+=(float)_envelope_a*100./SAMPLE_RATE;
            if (_envelope_volume>=255) _adsr_mode=mode_d;
        break;

        case mode_d:
            _envelope_volume-=(float)_envelope_d*100./SAMPLE_RATE;
            if (_envelope_volume<=_envelope_s) _adsr_mode=mode_s;
        break;

        case mode_s:

        break;

        case mode_r:
            _envelope_volume-=(float)_envelope_r*100./SAMPLE_RATE;
            if (_envelope_volume<=0) _envelope_volume=0;
        break;


    }

    return _envelope_volume/256.;
    //return 1.;
}

float Instrument::play() {

    float output=0;

    _phase+=_frequency/SAMPLE_RATE;
    while(_phase>1.) _phase-=1.;
	while(_phase<0.) _phase+=1.;

    switch(_waveform) {
        case square:   output = playSquare(); break;
        case sinus: output = playSin(); break;
        case triangle: output = playTriangle(); break;
        case saw: output=playSaw(); break;
        case noise: output=playNoise(); break;

    }

    _duration_left --;

    output*=_volume*getEnvelope()*90.;

    return output;
}


float Instrument::playSin() {
    return sin(_phase*2*M_PI);
}

float Instrument::playSaw() {
    return _phase*2.-1.;
}

float Instrument::playTriangle() {
    if (_phase<.5) return _phase*4.-1.;
	return 3-_phase*4;
}

float Instrument::playSquare() {
    if (_phase<_duty_cycle) return 1.;
    return -1.;
}

float Instrument::playNoise() {
    return (float)(rand()%65536)/32768-1;
}
