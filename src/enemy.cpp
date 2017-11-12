#include "enemy.h"

void Enemy::init(int x, int y){
  xPos = x;
  yPos = y;
  speed = 1;
  health = 100;

  enemyRect = {xPos, yPos, width, height};
}

void Enemy::update(int playerX, int playerY){
  if(playerX > xPos) {
    xPos+=speed;
  }
  if(playerX < xPos) {
    xPos-=speed;
  }
  if(playerY > yPos) {
    yPos+=speed;
  }
  if(playerY < yPos) {
    yPos-=speed;
  }

  enemyRect.x = xPos;
  enemyRect.y = yPos;
}

bool Enemy::isHit(SDL_Rect bullRect) {
  if(bullRect.x + bullRect.w > enemyRect.x &&
     bullRect.x < enemyRect.x + enemyRect.w &&
     bullRect.y + bullRect.h > enemyRect.y &&
     bullRect.y < enemyRect.y + enemyRect.h) {
       cout << "HITTT" << endl;
       return true;
     }
  return false;
}

void Enemy::draw(Graphics &graphics){
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &enemyRect);
}

void Enemy::clean(){

}
