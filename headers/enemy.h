#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "globals.h"
#include <vector>
using namespace std;

class Enemy {

public:
  void init(int x, int y);
  void update(int playerX, int playerY);
  bool isHit(SDL_Rect bullRect);
  void draw(Graphics &graphics);
  void clean();

  int getX();
  int getY();

private:
  int xPos, yPos, speed, health;
  int width = 30;
  int height = 30;

  SDL_Rect enemyRect;
};

#endif
