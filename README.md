# chiptune

A small tool for creating chiptune music (see example/mario.mp3 to get the idea).

The input is a binary file (.tune) formatted like this :

1 note  = 8 bytes (multibytes parameters are big-endian)-->
  * 2 bytes : tick, an integer representing the starting time of a note, the unit is Song._ticks_per_second
  * 1 byte : track, the track number
  * 1 byte : note, same as a MIDI note ( La 440 = 69), 1 unit is a half-tone
  * 1 byte : volume, 0=min, 127=max
  * 2 bytes : duration, same unit as tick
  * 1 byte : future use

The instruments availables are :
  * square wave ( with duty cycle as a parameter)
  * triangle
  * saw
  * sinus
  * noise

There is an ADSR volume envelope with 4 parameters (0-255) :
  * A : attack time, volume up 1 unit every 10ms, until 255.
  * D : decay time, volume down 1 unit until reaching S value
  * S : sustain volume, constant until note off
  * R : release time (after note off), volume down 1 unit every 10ms until 0.

For now the instruments are hardcoded in Song::load (should go in the .tune file)


STATUS :

  super pre-alpha !
  
COMPILE :

You will need SDL2, SDL2_mixer, and libsndfile (dev packages).
 
 
TODO :

  * Add CLI parameters (.tune file)
  * Add instruments definitions in the .tune file
  * Add tempo in the .tune file
  * normalize volume of the sample
  * Need many more effects !
