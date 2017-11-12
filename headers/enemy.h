#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "globals.h"

class Enemy {

public:
  void init(int x, int y);
  void update();
  bool isHit(SDL_Rect bullRect);
  void draw(Graphics &graphics);
  void clean();

private:
  int xPos, yPos, speed, health;
  int width = 50;
  int height = 50;

  SDL_Rect enemyRect;
};

#endif
