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

int Player::getXPos() {
  return xPos;
}

int Player::getYPos() {
  return yPos;
}

vector<Bullet> Player::getBullets() {
  return bullets;
}

void Player::shoot(int mouseX, int mouseY) {
  Bullet bull;
  int bullX = (xPos + width) - (width / 2);
  int bullY = (yPos + height) - (height / 2);
  int opposite = mouseY - bullY;
  int adjacent = mouseX  - bullX;
  float angle = atan2(opposite, adjacent) * 180 / PI;

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

  // Draw bullets before player
  for(int i = 0; i < bullets.size(); i++) {
    // Remove bullets from vector if off screen
    if(bullets[i].outOfBounds()) {
      bullets.erase(bullets.begin() + i);
    }
    bullets[i].update();
    bullets[i].draw(graphics);
  }

  int opposite = mouseY - yPos;
  int adjacent = mouseX  - xPos;
  float angle = atan2(opposite, adjacent) * 180 / PI;
  SDL_RenderCopyEx(graphics.getRenderer(), playerTex, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);

  // Non-rotated top left vertex
  SDL_Rect tempR = {xPos, yPos, 5, 5};

  // Rotated top left vertex
  float ang = angle * PI / 180;
  int rX = (xPos - 25)*cos(ang) - (yPos - 25)*sin(ang) + 25;
  int rY = (xPos - 25)*sin(ang) + (yPos - 25)*cos(ang) + 25;
  SDL_Rect tempR2 = {rX, rY, 5, 5};

  SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &tempR);
  SDL_RenderFillRect(graphics.getRenderer(), &tempR2);
}

void Player::clean() {
  SDL_DestroyTexture(playerTex);
  cout << "Cleaned up player..." << endl;
}
