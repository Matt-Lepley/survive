#include "bullet.h"

void Bullet::init(int x, int y, float a) {
  xPos = x;
  yPos = y;
  angle = a;
  width = 10;
  height = 10;
  speed = 1;

  bulletRect = {xPos, yPos, width, height};
}

void Bullet::update(float x, float y) {
  float dx = cos(angle) * speed;
  float dy = sin(angle) * speed;

  xPos += dx;
  yPos += dy;

  bulletRect.x = xPos;
  bulletRect.y = yPos;
}

void Bullet::draw(Graphics &graphics) {
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &bulletRect);
}
