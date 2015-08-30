#include <iostream>

using namespace std;

#include "Song.h"

int main()
{
    cout << "PlayTune" << endl;

    Song song;

    song.load("example/mario.tune");
    //song.load("example/vampirekiller.tune");

    song.infos();
    song.prepare();
    song.play();
    //song.save("example/mario.wav");

    return 0;
}
