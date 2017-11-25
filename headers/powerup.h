#ifndef POWERUP_H
#define POWERUP_H

#include "globals.h"
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

class Powerup {

public:
  void init(int val);
  int timeleft();
  void clean();

private:
  int value; // Global enum
  int timerDuration;
  int timerStart;
  Mix_Chunk *sound = NULL;
  bool hasPowerup = false;
  array<string, 2> sounds = {{"doubleSpeed.wav","nuke.wav"}};
  array<int, 2> durations = {{750, 2000}};
};

#endif
