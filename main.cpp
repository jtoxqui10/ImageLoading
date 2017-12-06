#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cerrno>
#include <cstring>
#include "frame.h"
#include "image.h"

typedef unsigned char byte;

using namespace std;

const double frames_per_second = 30; 
const int duration_in_seconds = 3;

Frame frame(720, 480);

int main(int argc, char * argv[]) {

	const char * cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " 
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " 
		"-i -                " 
		"-pix_fmt yuv420p    " 
		"-vcodec mpeg4       "
		"-an                 " 
		"-q:v 5              " 
		"output.mp4          ";

#ifdef _WIN32
	FILE * pipe = _popen(cmd, "wb");
#else
	FILE * pipe = popen(cmd, "w");
#endif
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}

	Image image;
	image.load("applelogo.png", 200, 200);
	image.setVelocity(100, 0);
	image.setStartingpts(100, 100);

	Image image2;
	image2.load("rose.png", 100, 100);
	image2.setVelocity(10, 0);
	image2.setStartingpts(0, 0);
	
	int num_frames = duration_in_seconds * frames_per_second;
		for (int i = 0; i < num_frames; ++i) {
			double dt = i / frames_per_second;
			if (dt > 1.0 / 60.0) {
				frame.clear();

				image.draw();
				image2.draw();
				
				image.update(dt);
				image2.update(dt);

				frame.write(pipe);

			}	
		}

	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
