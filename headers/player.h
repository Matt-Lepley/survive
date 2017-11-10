#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "bullet.h"

#include <vector>

class Player {

public:

  void init();
  void update();
  void draw(Graphics &graphics);
  void clean();

private:
  int x, y, speed, health;
  int width = 50;
  int height = 50;

  vector<Bullet> bullets = {};

  SDL_Event event;
  SDL_Rect playerRect;
};

#endif
