# chiptune

A small tool for creating chiptune music (see example/mario.mp3 to get the idea).

The input is a binary file (.tune) formatted like this:

1 note  = 8 bytes (multibytes parameters are big-endian)-->
  * 2 bytes : tick, an integer representing the starting time of a note, the unit is Song._ticks_per_second
  * 1 byte : track, the track number
  * 1 byte : note, same as a MIDI note ( La 440 = 69), 1 unit is a half-tone
  * 1 byte : volume, 0=min, 127=max
  * 2 bytes : duration, same unit as tick
  * 1 byte : future use

The instruments availables are:
  * square wave ( with duty cycle as a parameter)
  * triangle
  * saw
  * sinus
  * noise

There is an ADSR volume envelope with 4 parameters (0-255) :
  * A : attack time, volume up "A" units every 10ms, until 255.
  * D : decay time, volume down "D" units every 10ms, until reaching S value
  * S : sustain volume, constant until note off
  * R : release time (after note off), volume down "R" units every 10ms until 0.

For now the instruments are hardcoded in Song::load (should go in the .tune file)


STATUS :

  super pre-alpha !
  
COMPILE :

You will need SDL2, SDL2_mixer, and libsndfile (dev packages).

apt-get install libsndfile1-dev libsdl2-mixer-dev for debian / ubuntu based distros.

RUNNING :

$ ./playtune 
Playtune command help:
-t <filename.tune> : open a .tune file
-i : get tune infos
-p : play the tune
-h : help
 
$ ./playtune -t example/mario.tune -p
PlayTune
Loading example/mario.tune ...
Playing ...

 
TODO :

  * Add instruments definitions in the .tune file
  * Add tempo in the .tune file
  * normalize volume of the sample
  * Need many more effects !
