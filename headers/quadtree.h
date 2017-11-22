#ifndef QUADTREE_H
#define QUADTREE_H

#include "globals.h"
#include "enemy.h"

#include <SDL2/SDL.h>

class Quadtree {

public:

private:

  const int MAX_OBJECTS = 10;
  const int MAX_LEVELS = 5;

  int currentLevel;
  vector<Enemy> enemies = {};
  vector<Quadtree> nodes = {};
  SDL_Rect boundsRect;
};

#endif
