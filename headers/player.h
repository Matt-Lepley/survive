#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "bullet.h"
#include "globals.h"

#include <vector>
#include <cmath>

class Player {

public:

  void init(Graphics &graphics);
  void shoot();
  void update();
  void draw(Graphics &graphics);
  void clean();

  void setMouseX(int x);
  void setMouseY(int y);

private:
  int xPos, yPos, speed, health;
  int width = 50;
  int height = 50;
  int mouseX, mouseY;

  vector<Bullet> bullets = {};

  SDL_Event event;
  SDL_Rect playerRect;
  SDL_Surface *playerSurface;
  SDL_Texture *playerTex;
};

#endif
