#include "player.h"

void Player::init(Graphics &graphics) {
  cout << "initializing player.." << endl;
  xPos = (SCREEN_WIDTH / 2) - (width / 2);
  yPos = (SCREEN_HEIGHT / 2) - (height / 2);
  speed = 3;
  health = 100;

  mouseX = xPos;
  mouseY = yPos;

  playerRect = {xPos, yPos, width, height};

  playerSurface = IMG_Load("player.png");
  playerTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), playerSurface);
  SDL_FreeSurface(playerSurface);

  cout << "done initializing player!" << endl;
}

void Player::shoot(int mouseX, int mouseY) {
  Bullet bull;
  int bullX = (xPos + width) - 5;
  int bullY = (yPos + height) - (height / 2);
  int opposite = mouseY - bullX;
  int adjacent = mouseX  - bullY;
  float angle = atan2(opposite, adjacent) * 180 / 3.14159265;

  bull.init(bullX, bullY, angle);
  bullets.push_back(bull);
}

void Player::setMouseX(int x) {
  mouseX = x;
}

void Player::setMouseY(int y) {
  mouseY = y;
}

void Player::update() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if(keyState[SDL_SCANCODE_F] || keyState[SDL_SCANCODE_RIGHT]) {
			xPos += speed;
	}

	if(keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_LEFT]) {
			xPos -= speed;
	}

  if(keyState[SDL_SCANCODE_E] || keyState[SDL_SCANCODE_UP]) {
      yPos -= speed;
  }

  if(keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_DOWN]) {
      yPos += speed;
  }

  playerRect.x = xPos;
  playerRect.y = yPos;
}

void Player::draw(Graphics &graphics) {
  int opposite = mouseY - yPos;
  int adjacent = mouseX  - xPos;
  float angle = atan2(opposite, adjacent) * 180 / 3.14159265;
  SDL_RenderCopyEx(graphics.getRenderer(), playerTex, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);
  // SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  // SDL_RenderFillRect(graphics.getRenderer(), &playerRect);

  for(int i = 0; i < bullets.size(); i++) {
    bullets[i].update(sin(angle), cos(angle));
    bullets[i].draw(graphics);
  }
}

void Player::clean() {
  SDL_DestroyTexture(playerTex);
  cout << "Cleaned up player..." << endl;
}