#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include "graphics.h"

#include <SDL2/SDL_mixer.h>
#include <random>
#include <iostream>
using namespace std;

class Camera {

public:

	void init();
	void draw(Graphics &graphics);
	void shake();
	bool getShaking();
	void clean();
	SDL_Rect getRect();

private:
	SDL_Rect cameraRect;
	int startedShaking  = 0;
	int shakeDuration = 750;
	bool shaking = false;

	Mix_Chunk *nuke = NULL;
};

#endif
