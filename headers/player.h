#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"
#include "bullet.h"
#include "globals.h"
#include "gameobject.h"
#include "enemy.h"
#include "powerup.h"

#include <array>
#include <vector>
#include <cmath>
#include <SDL2/SDL_mixer.h>

class Player {

public:

  void init(Graphics &graphics);
  void shoot(int mouseX, int mouseY, Graphics &graphics);
  void destroyBullet(int index);
  void update();
  void draw(Graphics &graphics, SDL_Rect cameraRect);
  void clean();

  int getXPos();
  int getYPos();
  int getW();
  int getH();
  int getHealth();

  void setMouseX(int x);
  void setMouseY(int y);
  bool collision(Gameobject obj, vector<Enemy>* enemies);
  bool outOfBounds();
  void enemyCollision(Graphics &graphics, vector<Enemy> *enemies);

  void handlePowerups(vector<Enemy>* enemies);
  void removeDuplicatePowerups(int value);

  void giveDoubleSpeed();
  void removeDoubleSpeed();

  void nuke(vector<Enemy>* enemies);

  void freezeEnemies(vector<Enemy>* enemies);
  void unfreezeEnemies(vector<Enemy>* enemies);

  vector<Bullet> getBullets();
  SDL_Rect *getDoubleSpeedTimerRect();
  SDL_Rect *getFreezeTimerRect();

private:
  int xPos, yPos, speed, health;
  int baseSpeed = 3;
  float angle = 0;
  int width = 50;
  int height = 50;
  int mouseX, mouseY;
  int lastHit = 0;
  int maxHealth;

  bool doubleSpeed = false;

  vector<Bullet> bullets = {};
  vector<Powerup> powerups = {};
  SDL_Rect doubleSpeedTimerRect;
  SDL_Rect freezeTimerRect;

  array<SDL_Rect, 2> timerRects = {{
    doubleSpeedTimerRect,
    freezeTimerRect
  }};

  SDL_Event event;
  SDL_Rect playerRect;
  SDL_Rect healthRect;
  SDL_Rect maxHealthRect;
  SDL_Surface *playerSurface;
  SDL_Texture *playerTex;

  Mix_Chunk *damageFromEnemyChunk = NULL;
  Mix_Chunk *shotChunk = NULL;
};

#endif
