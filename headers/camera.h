#ifndef CAMERA_H
#define CAMERA_H

#include "globals.h"
#include "graphics.h"

#include <SDL2/SDL.h>
#include <random>
#include <iostream>
using namespace std;

class Camera {

public:

	Camera();
	void draw(Graphics &graphics);
	void shake();
	bool getShaking();
	SDL_Rect getRect();

private:
	SDL_Rect cameraRect;
	int startedShaking  = 0;
	int shakeDuration = 750;
	bool shaking = false;
};

#endif
