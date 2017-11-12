#ifndef BULLET_H
#define BULLET_H

#include "globals.h"
#include "graphics.h"

class Bullet {

public:
  void init(float x, float y, float a);
  void update();
  bool outOfBounds();
  void draw(Graphics &graphics);

private:
  int width, height, speed;
  float xPos, yPos, angle;
  SDL_Rect bulletRect;
};

#endif
