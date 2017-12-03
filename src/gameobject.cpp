#include "gameobject.h"

void Gameobject::init(int dropValue, int eX, int eY, Graphics &graphics) {
  value = dropValue;
  xPos = eX;
  yPos = eY;
  objRect = {xPos, yPos, width, height};

  objSurface = IMG_Load(sprites[value].c_str());
  objTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), objSurface);
  SDL_FreeSurface(objSurface);
}

void Gameobject::draw(Graphics &graphics) {
  SDL_RenderFillRect(graphics.getRenderer(), &objRect);
  SDL_RenderCopy(graphics.getRenderer(), objTexture, NULL, &objRect);
}

SDL_Rect Gameobject::getRect() {
  return objRect;
}

int Gameobject::getDropValue() {
  return value;
}

void Gameobject::clean() {
  SDL_DestroyTexture(objTexture);
  cout << "Cleaned gameobject!" << endl;
}
