#ifndef GLOBALS_H
#define GLOBALS_H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PI = 3.14159265;

enum DROPS {
  DoubleSpeed,
  Nuke,
  NUM_DROPS
};

enum GAMESTATES {
  StartMenu,
  Playing,
  Paused,
  Gameover
};

#endif
