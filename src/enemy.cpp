#include "enemy.h"

void Enemy::init(int x, int y){
  xPos = x;
  yPos = y;
  speed = 1;
  health = 100;

  enemyRect = {xPos, yPos, width, height};
}

int Enemy::getX() {
  return xPos;
}

int Enemy::getY() {
  return yPos;
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

  // int tempX, tempY;
  // vector<pair<int, int>> coords = {};
  //
  // // Top left
  // tempX = xPos;
  // tempY = yPos;
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // Top right
  // tempX = xPos + width;
  // tempY = yPos;
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // bottom right
  // tempX = xPos + width;
  // tempY = yPos + height;
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // bottom left
  // tempX = xPos;
  // tempY = yPos + height;
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  // // Draw vertices rects
  // for(int i = 0; i < coords.size(); i++) {
  //   SDL_Rect tempR = {coords[i].first, coords[i].second, 2, 2};
  //   SDL_RenderFillRect(graphics.getRenderer(), &tempR);
  // }

  // Draw perp rects
  // SDL_SetRenderDrawColor(graphics.getRenderer(), 225, 55, 100, 255);
  // for(int i = 0; i < coords.size(); i++) {
  //   pair<int,int> p1 = coords[i];
  //   pair<int,int> p2 = coords[i + 1 == coords.size() ? 0 : i + 1];
  //   int tempX = p1.first - p2.first;
  //   int tempY = p1.second - p2.second;
  //   pair<int,int> perpEdge = {tempX + xPos + (width/2), tempY + yPos + (height/2)};
  //   SDL_Rect tempR = {perpEdge.first, perpEdge.second, 5, 5};
  //   SDL_RenderFillRect(graphics.getRenderer(), &tempR);
  // }
}

void Enemy::clean(){

}
