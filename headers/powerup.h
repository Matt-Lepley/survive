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

  int getValue();
  int getTimerDuration();

private:
  int value; // Global enum
  int timerDuration;
  int timerStart;
  Mix_Chunk *sound = NULL;
  bool hasPowerup = false;
  array<string, 3> sounds = {{"doubleSpeed.wav", "nuke.wav", "freeze2x.wav"}};
  array<int, 3> durations = {{8000, 750, 6000}};
};

#endif
