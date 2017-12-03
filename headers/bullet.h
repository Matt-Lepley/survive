#ifndef BULLET_H
#define BULLET_H

#include "globals.h"
#include "graphics.h"

class Bullet {

public:
  void init(float x, float y, float a, Graphics &graphics);
  void update();
  bool outOfBounds();
  void draw(Graphics &graphics);
  void clean();

  SDL_Rect getRect();

private:
  int width, height, speed;
  float xPos, yPos, angle;

  SDL_Rect bulletRect;
  SDL_Texture *bulletTexture;
  SDL_Surface *bulletSurface;
};

#endif
