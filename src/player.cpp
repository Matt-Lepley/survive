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
  int adjacent = mouseX - xPos;
  float angle = atan2(opposite, adjacent) * 180 / PI;
  SDL_RenderCopyEx(graphics.getRenderer(), playerTex, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);


  // Covert angle to radians
  float ang = angle * PI / 180;

  // Top left
  // Start at -25, -25 (assuming player is 50x50) so center is at 0,0
  int tlX = (-(width/2))*cos(ang) - (-(height/2))*sin(ang);
  int tlY = (-(width/2))*sin(ang) + (-(height/2))*cos(ang);
  // Move the rotated positions relative to player
  tlX += xPos + (width/2);
  tlY += yPos + (height/2);

  // Top right
  // Start at 25, -25 (assuming player is 50x50) so center is at 0,0
  int trX = (width/2)*cos(ang) - (-(height/2))*sin(ang);
  int trY = (width/2)*sin(ang) + (-(height/2))*cos(ang);
  // Move the rotated positions relative to player
  trX += xPos + (width/2);
  trY += yPos + (height/2);

  // bottom right
  // Start at 25, 25 (assuming player is 50x50) so center is at 0,0
  int brX = (width/2)*cos(ang) - (height/2)*sin(ang);
  int brY = (width/2)*sin(ang) + (height/2)*cos(ang);
  // Move the rotated positions relative to player
  brX += xPos + (width/2);
  brY += yPos + (height/2);

  // bottom left
  // Start at -25, 25 (assuming player is 50x50) so center is at 0,0
  int blX = (-(width/2))*cos(ang) - (height/2)*sin(ang);
  int blY = (-(width/2))*sin(ang) + (height/2)*cos(ang);
  // Move the rotated positions relative to player
  blX += xPos + (width/2);
  blY += yPos + (height/2);

  // Draw
  SDL_Rect topLeftR = {tlX, tlY, 5, 5};
  SDL_Rect topRightR = {trX, trY, 5, 5};
  SDL_Rect bottomRightR = {brX, brY, 5, 5};
  SDL_Rect bottomLeftR = {blX, blY, 5, 5};

  SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &topLeftR);
  SDL_RenderFillRect(graphics.getRenderer(), &topRightR);
  SDL_RenderFillRect(graphics.getRenderer(), &bottomRightR);
  SDL_RenderFillRect(graphics.getRenderer(), &bottomLeftR);
}

void Player::clean() {
  SDL_DestroyTexture(playerTex);
  cout << "Cleaned up player..." << endl;
}
