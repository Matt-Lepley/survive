#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "bullet.h"
#include "globals.h"
#include "gameobject.h"
#include "enemy.h"

#include <vector>
#include <cmath>

class Player {

public:

  void init(Graphics &graphics);
  void shoot(int mouseX, int mouseY);
  void destroyBullet(int index);
  void update();
  void draw(Graphics &graphics);
  void clean();

  int getXPos();
  int getYPos();
  void setMouseX(int x);
  void setMouseY(int y);
  bool collision(Gameobject obj, vector<Enemy>* enemies);
  void enemyCollision(Graphics &graphics, vector<Enemy> *enemies);
  void handleBuff(int value, vector<Enemy>* enemies);
  void alterSpeed();
  void nuke(vector<Enemy>* enemies);

  vector<Bullet> getBullets();

private:
  int xPos, yPos, speed, health;
  float angle = 0;
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
