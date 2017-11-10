#include "player.h"
#include "globals.h"

void Player::init() {
  x = (SCREEN_WIDTH / 2) - (width / 2);
  y = (SCREEN_HEIGHT / 2) - (height / 2);
  speed = 3;
  health = 100;

  playerRect = {x, y, width, height};
}

void Player::update() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if(keyState[SDL_SCANCODE_SPACE]) {
		cout << "SHOTS FIRED!" << endl;

      cout << bullets.size() << endl;
      // Why does this need to be a single char?
      // anything longer than one letter causes crash...
      Bullet b;
      b.init(1,1);
      bullets.push_back(b);
      cout << bullets.size() << endl;
	}

	if(keyState[SDL_SCANCODE_F] || keyState[SDL_SCANCODE_RIGHT]) {
			x += speed;
	}

	if(keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_LEFT]) {
			x -= speed;
	}

  if(keyState[SDL_SCANCODE_E] || keyState[SDL_SCANCODE_UP]) {
      y -= speed;
  }

  if(keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_DOWN]) {
      y += speed;
  }

  playerRect.x = x;
  playerRect.y = y;
}

void Player::draw(Graphics &graphics) {
  // for(int i = 0; i < bullets.size(); i++) {
  //
  // }
  SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &playerRect);
}

void Player::clean() {

}
