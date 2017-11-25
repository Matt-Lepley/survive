#include "powerup.h"

void Powerup::init(int val, int duration, string file) {
  value = val;
  timerDuration = duration;
  sound = Mix_LoadWAV(file.to_cstr());
  Mix_PlayChannel(-1, sound, 0);
}

int Powerup::timeleft() {
  if(timerStart + timerDuration > SDL_GetTicks()) {
    return (timerStart + timerDuration) - SDL_GetTicks();
  } else {
    return 0;
  }
}

void Powerup::clean() {
  Mix_FreeChunk(sound);
}
