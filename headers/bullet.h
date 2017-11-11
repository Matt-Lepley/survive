#ifndef BULLET_H
#define BULLET_H

#include "globals.h"
#include "graphics.h"

class Bullet {

public:
  void init(int x, int y, float a);
  void update(float x, float y);
  void draw(Graphics &graphics);

private:
  int xPos, yPos, width, height, speed;
  float angle;
  SDL_Rect bulletRect;
};

#endif
