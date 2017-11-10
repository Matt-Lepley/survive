#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "globals.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

class Graphics {

public:
  void init();
  void clear();
  SDL_Renderer *getRenderer();
  void clean();

private:
  SDL_Window *gameWindow;
  SDL_Renderer *gameRenderer;
};

#endif
