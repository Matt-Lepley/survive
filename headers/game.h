#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "graphics.h"
#include "player.h"
#include "enemy.h"
#include "gameobject.h"
#include "camera.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
using namespace std;

class Game {

public:

  void init();
  void capFrames();
  void handleEvents();

  int getGamestate();

  void populateSpawnPoints();
  pair<int, int> enemySpawnPoint();

  void generateEnemies();
  bool shouldDropItem();
  int itemDropType();
  void dropItem(Enemy enemy);

  void startMenuLoop();
  void gameloop();
  void clean();

  bool isRunning();
  SDL_Renderer *getRenderer();

private:
  const int FPS = 60;						// Frames per second
	const int MAX_FRAME_TIME = 1000 / FPS;	// Max time a frame can take
	int LAST_UPDATE = 0;
  int CURRENT_TIME, ELAPSED_TIME;

  bool gameIsRunning = true;
  
  SDL_Event event;
  SDL_Rect screenRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Rect startGameRect = {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};
  SDL_Rect quitGameRect = {SCREEN_WIDTH / 2 - 150, startGameRect.y + 150, 300, 100};

  // Objects
  Graphics graphics;
  Camera camera;
  Player player;
  vector<Enemy> enemies = {};
  vector<Gameobject> drops = {};
  int wave = 1;
  vector<pair<int, int>> spawnPoints = {};
  int gamestate = GAMESTATES::StartMenu;
};

#endif
