#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics.h"
#include "globals.h"

class Gameobject {

public:
  void init(int dropValue, int eX, int eY);
  void draw(Graphics &graphics);
  SDL_Rect getRect();
  int getDropValue();

private:
  int xPos, yPos, value;
  int width = 30;
  int height = 30;
  SDL_Rect objRect;

};

#endif
