#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "globals.h"
#include <vector>
using namespace std;

class Enemy {

public:
  void init(Graphics &graphics, int x, int y);
  void update(int playerX, int playerY, int playerW, int playerH);
  bool isHit(SDL_Rect bullRect);
  void draw(Graphics &graphics, int playerX, int playerY, SDL_Rect cameraRect);
  void clean();

  int getX();
  int getY();
  int getW();
  int getH();

private:
  int xPos, yPos, speed, health;
  int width = 30;
  int height = 30;

  SDL_Rect enemyRect;
  SDL_Surface *enemySurface;
  SDL_Texture *enemyTex;
};

#endif
