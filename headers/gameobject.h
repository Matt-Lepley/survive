#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics.h"
#include "globals.h"
#include <string>
#include <array>

class Gameobject {

public:
  void init(int dropValue, int eX, int eY, Graphics &graphics);
  void draw(Graphics &graphics);
  SDL_Rect getRect();
  int getDropValue();
  void clean();

private:
  int xPos, yPos, value;
  int width = 30;
  int height = 30;

  array<string, 3> sprites = {{"doubleSpeed.png", "tnt.png", "freeze.png"}};

  SDL_Rect objRect;
  SDL_Surface *objSurface;
  SDL_Texture *objTexture;
};

#endif
