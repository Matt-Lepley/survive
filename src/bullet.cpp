#include "bullet.h"

void Bullet::init(float x, float y, float a) {
  xPos = x;
  yPos = y;
  angle = a;
  width = 10;
  height = 10;
  speed = 3;

  bulletRect = {int(xPos), int(yPos), width, height};
}

SDL_Rect Bullet::getRect() {
  return bulletRect;
}

void Bullet::update() {
  float dirx = cos(angle * PI/180);
  float diry = sin(angle * PI/180);

  xPos += dirx * speed;
  yPos += diry * speed;

  bulletRect.x = xPos;
  bulletRect.y = yPos;
}

bool Bullet::outOfBounds() {
  if(xPos < 0 || xPos > SCREEN_WIDTH ||
     yPos < 0 || yPos > SCREEN_HEIGHT) {
    return true;
  }
  return false;
}

void Bullet::draw(Graphics &graphics) {
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &bulletRect);
}
