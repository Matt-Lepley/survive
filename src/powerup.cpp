#include "powerup.h"

void Powerup::init(int val) {
  value = val;
  timerStart = SDL_GetTicks();
  timerDuration = durations[value];
  sound = Mix_LoadWAV(sounds[value].c_str());
  Mix_PlayChannel(-1, sound, 0);
}

int Powerup::timeleft() {
  if(timerStart + timerDuration > SDL_GetTicks()) {
    return (timerStart + timerDuration) - SDL_GetTicks();
  } else {
    return 0;
  }
}

int Powerup::getValue() {
  return value;
}

int Powerup::getTimerDuration() {
  return timerDuration;
}

void Powerup::clean() {
  Mix_FreeChunk(sound);
}
