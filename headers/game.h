#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "graphics.h"
#include "player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

class Game {

public:

  void init();
  void capFrames();
  void handleEvents();
  void gameloop();
  void clean();

  bool isRunning();
  SDL_Renderer *getRenderer();

private:
  const int FPS = 60;						// Frames per second
	const int MAX_FRAME_TIME = 1000 / FPS;	// Max time a frame can take
	int LAST_UPDATE, CURRENT_TIME, ELAPSED_TIME;

  bool gameIsRunning = true;

  SDL_Event event;
  Graphics graphics;
  Player player;
};

#endif
