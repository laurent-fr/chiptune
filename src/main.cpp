#include <iostream>
#include <unistd.h>


using namespace std;

#include "Song.h"


void show_help() {

    cout << "Playtune command help :" << endl;
    cout << "-t <filename.tune> : open a .tune file" << endl;
    cout << "-i : get tune infos" << endl;
    cout << "-p : play the tune" << endl;
    cout << "-h : help" << endl;

}

int main(int argc, char** argv)
{

    int c;
	bool flag_play=false;
	bool flag_infos=false;
	bool flag_tune=false;
    bool flag_help=false;
	char *filename=NULL;

	while((c = getopt (argc, argv, "t:iph")) != -1) {

		switch(c) {

			case 't': flag_tune=true; filename = strdup(optarg);
			break;

			case 'i': flag_infos=true;
			break;

			case 'p': flag_play=true;
			break;

            case 'h': flag_help=true;
            break;

            default:
                flag_help=true;
                break;

		}
    }

    if ((flag_help==true)||(argc==1)) {
        show_help();
        exit(0);
    }


    cout << "PlayTune" << endl;

    Song song;

	if (flag_tune==true) {
	cout << "Loading " << filename << " ..." << endl ;
	    song.load(filename);
	}

	if (flag_infos==true) {
	    song.infos();
	}

    

	if (flag_play==true) {
	    cout << "Playing ..." << endl;
	    song.prepare();
	    song.play();
	}

    //song.save("example/mario.wav");

    return 0;
}
