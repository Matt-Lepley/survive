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
  void shoot(int mouseX, int mouseY);
  void update();
  void draw(Graphics &graphics);
  void clean();

  void setMouseX(int x);
  void setMouseY(int y);

  vector<Bullet> getBullets();

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
