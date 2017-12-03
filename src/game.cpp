#include "game.h"

void Game::init() {
  cout << "initializing game.." << endl;
  TTF_Init();
  menuFont = TTF_OpenFont("leadcoat.ttf", 80);
  populateSpawnPoints();
  graphics.init();
  camera.init();
  player.init(graphics);
  cout << "done initializing game!" << endl;
}

int Game::getGamestate() {
  return gamestate;
}

void Game::generateEnemies() {
  if(enemies.size() == 0) {
    for(int i = 0; i < (wave * 5); i++) {
      Enemy enemy;
      pair<int, int> pos = enemySpawnPoint();
      enemy.init(graphics, pos.first, pos.second);
      enemies.push_back(enemy);
    }
    wave++;
  }
}

pair<int, int> Game::enemySpawnPoint() {
  random_device rd;
  mt19937 gen(rd());;
  uniform_int_distribution<int> dis(0, spawnPoints.size() - 1);
  uniform_int_distribution<int> dis2(-50, 50);

  int pos = dis(gen);
  int xoffset = dis2(gen);
  int yoffset = dis2(gen);

  pair<int, int> tempPair = spawnPoints[pos];
  tempPair.first += xoffset;
  tempPair.second += yoffset;

  return tempPair;
}

void Game::capFrames() {
	CURRENT_TIME = SDL_GetTicks();
	ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE;

	if (ELAPSED_TIME < MAX_FRAME_TIME) {
		SDL_Delay(MAX_FRAME_TIME - ELAPSED_TIME);
	}
}

bool Game::shouldDropItem() {
  random_device rd;
  mt19937 gen(rd());;
  uniform_int_distribution<int> dis(1, 100);

  // 15% chance to drop item
  return dis(gen) < 15 ? true : false;
}

int Game::itemDropType() {
  random_device rd;
  mt19937 gen(rd());;
  uniform_int_distribution<int> dis(0, DROPS::NUM_DROPS - 1);

  return dis(gen);
}

void Game::dropItem(Enemy enemy) {
  if(shouldDropItem()) {
    Gameobject g;
    g.init(itemDropType(), enemy.getX(), enemy.getY(), graphics);
    drops.push_back(g);
  }
}

void Game::handleEvents() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	while(SDL_PollEvent(&event) != 0) {

		// Exit game loop
		if(event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE]) {
			gameIsRunning = false;
		}

    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
      if(gamestate == GAMESTATES::Playing) {
        cout << "PLAYING" << endl;
        gamestate = GAMESTATES::StartMenu;
      } else {
        cout << "MENU" << endl;
        gamestate = GAMESTATES::Playing;
      }
    }

    if(event.type == SDL_MOUSEMOTION) {
      player.setMouseX(event.button.x);
      player.setMouseY(event.button.y);

      if(gamestate == GAMESTATES::StartMenu) {
        if(event.button.x > startGameRect.x &&
           event.button.x < startGameRect.x + startGameRect.w &&
           event.button.y > startGameRect.y &&
           event.button.y < startGameRect.y + startGameRect.h) {
             startHovered = true;
        } else {
          startHovered = false;
        }

        if(event.button.x > quitGameRect.x &&
           event.button.x < quitGameRect.x + quitGameRect.w &&
           event.button.y > quitGameRect.y &&
           event.button.y < quitGameRect.y + quitGameRect.h) {
             quitHovered = true;
        } else {
          quitHovered = false;
        }
      }
    }

		// Mouse events
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {

        if(gamestate == GAMESTATES::StartMenu) {
          if(event.button.x > startGameRect.x &&
             event.button.x < startGameRect.x + startGameRect.w &&
             event.button.y > startGameRect.y &&
             event.button.y < startGameRect.y + startGameRect.h) {
               gamestate = GAMESTATES::Playing;
               return;
          }

          if(event.button.x > quitGameRect.x &&
             event.button.x < quitGameRect.x + quitGameRect.w &&
             event.button.y > quitGameRect.y &&
             event.button.y < quitGameRect.y + quitGameRect.h) {
               gameIsRunning = false;
          }
        }

        if(gamestate == GAMESTATES::Playing) {
          player.shoot(event.button.x, event.button.y, graphics);
        }
			}
		}
	}
}

void Game::startMenuLoop() {
  graphics.clear();
  handleEvents();
  capFrames();  // Cap framerate before any rendering

  if(startHovered) {
    startColor = {255,0,0};
  } else {
    startColor = {0,0,0};
  }

  if(quitHovered) {
    quitColor = {255,0,0};
  } else {
    quitColor = {0,0,0};
  }

  // Start button
  textSurface = TTF_RenderText_Solid(menuFont, "start", startColor);
  startTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(startTexture, NULL, NULL, &rectW, &rectH);
  startGameRect = {(SCREEN_WIDTH / 2) - (rectW / 2), (SCREEN_HEIGHT / 2) - (rectH / 2), rectW, rectH};

  // Quit button
  textSurface = TTF_RenderText_Solid(menuFont, "quit", quitColor);
  quitTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), textSurface);
  SDL_FreeSurface(textSurface);

  SDL_QueryTexture(quitTexture, NULL, NULL, &rectW, &rectH);
  quitGameRect = {(SCREEN_WIDTH / 2) - (rectW / 2), (SCREEN_HEIGHT / 2) - (rectH / 2) + 100, rectW, rectH};

  SDL_SetRenderDrawColor(graphics.getRenderer(), 255,255,0,255);
  SDL_RenderFillRect(graphics.getRenderer(), &screenRect);

  SDL_RenderCopy(graphics.getRenderer(), startTexture, NULL, &startGameRect);
  SDL_RenderCopy(graphics.getRenderer(), quitTexture, NULL, &quitGameRect);

  SDL_RenderPresent(graphics.getRenderer());

  // Update for framerate capping
  LAST_UPDATE = CURRENT_TIME;
}

void Game::gameloop() {
  graphics.clear();
  handleEvents();
  capFrames();  // Cap framerate before any rendering

  generateEnemies();

  player.update();
  player.handlePowerups(&enemies);
  player.draw(graphics, camera.getRect());
  for(int i = 0; i < enemies.size(); i++) {
    for(int j = 0; j < player.getBullets().size(); j++) {
      if(enemies[i].isHit(player.getBullets()[j].getRect())) {
        dropItem(enemies[i]);
        enemies[i].clean();
        enemies.erase(enemies.begin() + i);
        player.destroyBullet(j);
      }
    }
    enemies[i].update(player.getXPos(), player.getYPos(), player.getW(), player.getH());
    for(int n = i + 1; n < enemies.size(); n++) {
      if(abs(enemies[i].getX() - enemies[n].getX()) <= 10 &&
         abs(enemies[i].getY() - enemies[n].getY()) <= 10) {
          enemies[i].createSpace();
          enemies[n].createSpace();
      }
    }
    enemies[i].draw(graphics, player.getXPos(), player.getYPos(), camera.getRect());
  }

  SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 255, 255);
  SDL_RenderFillRect(graphics.getRenderer(), player.getFreezeTimerRect());
  SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), player.getDoubleSpeedTimerRect());

  player.enemyCollision(graphics, &enemies);

  for(int i = 0; i < drops.size(); i++) {
    if(player.collision(drops[i], &enemies)) {
      if(drops[i].getDropValue() == DROPS::Nuke) {
        camera.shake();
      }
      drops[i].clean();
      drops.erase(drops.begin() + i);
    } else {
      drops[i].draw(graphics);  // Only draw if player hasn't picked up
    }
  }

  if(camera.getShaking()) {
    camera.shake();
  }

  SDL_RenderPresent(graphics.getRenderer());

  // Update for framerate capping
  LAST_UPDATE = CURRENT_TIME;
}

bool Game::isRunning() {
  return gameIsRunning;
}

void Game::clean() {
  player.clean();
  graphics.clean();
  camera.clean();
  SDL_DestroyTexture(startTexture);
  SDL_DestroyTexture(quitTexture);
  TTF_CloseFont(menuFont);
  TTF_Quit();
}

void Game::populateSpawnPoints() {
  ifstream file("spawnPoints.txt");
	string str;
	int counter = 0;
	while(getline(file, str)) {
    pair<int, int> tempPair;
		int startPos = 0;
		int col = 1;
		string path, temp;
		for(int i = 0; i < str.length(); i++) {
			if(str.substr(i,1) == ",") {
				if(col == 1) {
					tempPair.first = stoi(str.substr(startPos, i));
          col++;
          startPos = i;
				}
				if(col == 2) {
				  tempPair.second = stoi(str.substr(startPos + 1, str.length() - startPos + 1));
			  }
			}
		}
		spawnPoints.push_back(tempPair);
	}
	file.close();
}
