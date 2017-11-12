#include "game.h"

void Game::init() {
  cout << "initializing game.." << endl;
  graphics.init();
  player.init(graphics);
  enemy.init(100,100);
  cout << "done initializing game!" << endl;
}

void Game::capFrames() {
	CURRENT_TIME = SDL_GetTicks();
	ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE;

	if (ELAPSED_TIME < MAX_FRAME_TIME) {
		SDL_Delay(MAX_FRAME_TIME - ELAPSED_TIME);
	}
}

void Game::handleEvents() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	while(SDL_PollEvent(&event) != 0) {

		// Exit game loop
		if(event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE]) {
			gameIsRunning = false;
		}

    if(event.type == SDL_MOUSEMOTION) {
      // Get mouse x and mouse y
      // Get player x and player y
      // Find horizontal distance between
      // Find vertical distance between
      // Calculate angle
      player.setMouseX(event.button.x);
      player.setMouseY(event.button.y);
    }

		// Mouse events
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {

        player.shoot(event.button.x, event.button.y);
			}
		}
	}
}

void Game::gameloop() {

  graphics.clear();

  handleEvents();

  // Cap framerate before any rendering
  capFrames();

  player.update();
  player.draw(graphics);
  enemy.draw(graphics);

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
}
