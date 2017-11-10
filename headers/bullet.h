#ifndef BULLET_H
#define BULLET_H

#include "globals.h"
#include "graphics.h"

class Bullet {

public:
  void init(int x, int y);
  void update();
  void draw(Graphics &graphics);

private:
  int xPos, yPos, width, height, speed;
  SDL_Rect bulletRect;
};

#endif
