#include "enemy.h"

void Enemy::init(int x, int y){
  xPos = x;
  yPos = y;
  speed = 1;
  health = 100;

  enemyRect = {xPos, yPos, width, height};
}

void Enemy::update(){

}

void Enemy::draw(Graphics &graphics){
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &enemyRect);
}

void Enemy::clean(){

}
