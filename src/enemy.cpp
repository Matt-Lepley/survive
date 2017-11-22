#include "enemy.h"

void Enemy::init(Graphics &graphics, int x, int y){
  xPos = x;
  yPos = y;
  speed = 1;
  health = 100;

  enemyRect = {xPos, yPos, width, height};

  enemySurface = IMG_Load("enemy.png");
  enemyTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), enemySurface);
  SDL_FreeSurface(enemySurface);
}

int Enemy::getX() {
  return xPos;
}

int Enemy::getY() {
  return yPos;
}

int Enemy::getH() {
  return height;
}

int Enemy::getW() {
  return width;
}

void Enemy::update(int playerX, int playerY, int playerW, int playerH){
  if(playerX + (playerW / 2) > xPos) {
    xPos+=speed;
  }
  if(playerX + (playerW / 2) < xPos) {
    xPos-=speed;
  }
  if(playerY + (playerH / 2) > yPos) {
    yPos+=speed;
  }
  if(playerY + (playerH / 2) < yPos) {
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

void Enemy::draw(Graphics &graphics, int playerX, int playerY, SDL_Rect cameraRect){

  SDL_Rect transRect = enemyRect;
  transRect.x = enemyRect.x - cameraRect.x;
  transRect.y = enemyRect.y - cameraRect.y;

  int opposite = playerY - yPos;
  int adjacent = playerX - xPos;
  float angle = atan2(opposite, adjacent) * 180 / PI;
  SDL_RenderCopyEx(graphics.getRenderer(), enemyTex, NULL, &transRect, angle, NULL, SDL_FLIP_NONE);

  // SDL_RenderCopy(graphics.getRenderer(), enemyTex, NULL, &enemyRect);

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
  SDL_DestroyTexture(enemyTex);
  cout << "Cleaned up enemy..." << endl;
}
