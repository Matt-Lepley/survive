#include "bullet.h"

void Bullet::init(int x, int y) {
  x = x;
  y = y;
  width = 10;
  height = 10;
  speed = 3;

  bulletRect = {x, y, width, height};
}

void Bullet::move() {
  x += speed;
}

void Bullet::update() {
  move();

  bulletRect.x = x;
  bulletRect.y = y;
}

void Bullet::draw(Graphics &graphics) {
  update();
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &bulletRect);
}
