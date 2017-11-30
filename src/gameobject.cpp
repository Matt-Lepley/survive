#include "gameobject.h"

void Gameobject::init(int dropValue, int eX, int eY) {
  value = dropValue;
  xPos = eX;
  yPos = eY;
  objRect = {xPos, yPos, width, height};
}

void Gameobject::draw(Graphics &graphics) {
  if(value == DROPS::DoubleSpeed) {
    SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 100, 0, 255);
  } else if(value == DROPS::Nuke) {
    SDL_SetRenderDrawColor(graphics.getRenderer(), 100, 0, 100, 255);
  } else if(value == DROPS::Freeze) {
    SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 100, 255);
  }
  SDL_RenderFillRect(graphics.getRenderer(), &objRect);
}

SDL_Rect Gameobject::getRect() {
  return objRect;
}

int Gameobject::getDropValue() {
  return value;
}
