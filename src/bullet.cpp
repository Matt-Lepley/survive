#include "bullet.h"

void Bullet::init(float x, float y, float a, Graphics &graphics) {
  xPos = x;
  yPos = y;
  angle = a;
  width = 10;
  height = 10;
  speed = 3;

  bulletRect = {int(xPos), int(yPos), width, height};
  bulletSurface = IMG_Load("bullet.png");
  bulletTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), bulletSurface);
  SDL_FreeSurface(bulletSurface);
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
    clean();
    return true;
  }
  return false;
}

void Bullet::draw(Graphics &graphics) {
  SDL_RenderCopy(graphics.getRenderer(), bulletTexture, NULL, &bulletRect);
}

void Bullet::clean() {
  SDL_DestroyTexture(bulletTexture);
  cout << "Bullet cleaned!" << endl;
}
