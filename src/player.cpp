#include "player.h"

void Player::init(Graphics &graphics) {
  cout << "initializing player.." << endl;
  xPos = (SCREEN_WIDTH / 2) - (width / 2);
  yPos = (SCREEN_HEIGHT / 2) - (height / 2);
  speed = baseSpeed;
  health = 100;
  maxHealth = health;

  mouseX = xPos;
  mouseY = yPos;

  playerRect = {xPos, yPos, width, height};
  healthRect = {xPos - (health / 2), yPos - 50, health, 10};
  maxHealthRect = {healthRect.x - 2, healthRect.y - 2, healthRect.w + 4, healthRect.h + 4};

  playerSurface = IMG_Load("player.png");
  playerTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), playerSurface);
  SDL_FreeSurface(playerSurface);

  doubleSpeedChunk = Mix_LoadWAV("doubleSpeed.wav");

  cout << "done initializing player!" << endl;
}

void Player::destroyBullet(int index) {
  bullets.erase(bullets.begin() + index);
}

int Player::getXPos() {
  return xPos;
}

int Player::getYPos() {
  return yPos;
}

int Player::getW() {
  return width;
}

int Player::getH() {
  return height;
}

SDL_Rect *Player::getDoubleSpeedTimerRect() {
  return &timerRects[0];
}

SDL_Rect *Player::getNukeTimerRect() {
  return &timerRects[1];
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

bool Player::outOfBounds() {
  if(xPos > 0 &&
     xPos + width < SCREEN_WIDTH &&
     yPos > 0 &&
     yPos + height < SCREEN_HEIGHT) {
       return false;
     }

  return true;
}

bool Player::collision(Gameobject obj, vector<Enemy>* enemies) {
  SDL_Rect tempR = obj.getRect();
  if(tempR.x + tempR.w > playerRect.x &&
     tempR.x < playerRect.x + playerRect.w &&
     tempR.y + tempR.h > playerRect.y &&
     tempR.y < playerRect.y + playerRect.h) {
       //handleBuff(obj.getDropValue(), enemies);


       removeDuplicatePowerups(obj.getDropValue());
       Powerup pu;
       pu.init(obj.getDropValue());
       powerups.push_back(pu);
       cout << powerups.size() << endl;

       return true;
     }
  return false;
}

void Player::removeDuplicatePowerups(int value) {
  for(int i = 0; i < powerups.size(); i++) {
    if(powerups[i].getValue() == value) {
      powerups[i].clean();
      powerups.erase(powerups.begin() + i);
    }
  }
}

void Player::handlePowerups() {
  for(int i = 0; i < powerups.size(); i++) {
    if(powerups[i].timeleft() == 0) {
      powerups[i].clean();
      powerups.erase(powerups.begin() + i);
      // doubleSpeedTimerRect.w = 0;
    } else {
      // cout << powerups[i].timeleft() << endl;
      cout << timerRects[powerups[i].getValue()].w << endl;
      timerRects[powerups[i].getValue()].w = powerups[i].timeleft() / 10;
      // if(powerups[i].getValue() == 0) {
      //   doubleSpeedTimerRect.w = powerups[i].timeleft() / 10;
      // }
    }
  }
}

void Player::handleBuff(int value, vector<Enemy>* enemies) {
  if(value == DROPS::DoubleSpeed) {
    alterSpeed();
  }
  if(value == DROPS::Nuke) {
    nuke(enemies);
  }
}

// Figure out timer for speed buffs
void Player::alterSpeed() {
  if(!doubleSpeed) {
    Mix_PlayChannel(-1, doubleSpeedChunk, 0);
    startedDoubleSpeed = SDL_GetTicks();
    doubleSpeed = true;
  }

  if(doubleSpeed && startedDoubleSpeed + doubleSpeedDuration > SDL_GetTicks()) {
    speed = baseSpeed * 2;
  }

  if(doubleSpeed && startedDoubleSpeed + doubleSpeedDuration <= SDL_GetTicks()) {
    doubleSpeed = false;
  }
}

void Player::nuke(vector<Enemy>* enemies) {
  cout << "DIE ALLL" << endl;
  enemies->clear();
}

void Player::update() {
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if(keyState[SDL_SCANCODE_F] || keyState[SDL_SCANCODE_RIGHT]) {
    int dToEdge = SCREEN_WIDTH - (xPos + width);
    if(dToEdge < speed) {
      xPos += dToEdge;
    } else {
      xPos += speed;
    }
	}

	if(keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_LEFT]) {
    if(xPos < speed) {
      xPos -= xPos;
    } else {
      xPos -= speed;
    }
	}

  if(keyState[SDL_SCANCODE_E] || keyState[SDL_SCANCODE_UP]) {
    if(yPos < speed) {
      yPos -= yPos;
    } else {
      yPos -= speed;
    }
  }

  if(keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_DOWN]) {
    int dToEdge = SCREEN_HEIGHT - (yPos + height);
    if(dToEdge < speed) {
      yPos += dToEdge;
    } else {
      yPos += speed;
    }
  }

  playerRect.x = xPos;
  playerRect.y = yPos;

  maxHealthRect.x = xPos - (maxHealth / 4);
  maxHealthRect.y = yPos - 50;

  healthRect.x = maxHealthRect.x + 2;
  healthRect.y = maxHealthRect.y + 2;
  healthRect.w = health;
}

bool Player::enemyCollision(Graphics &graphics, vector<Enemy> *enemies) {
  for(int i = 0; i < enemies->size(); i++) {
    if((*enemies)[i].getX() + (*enemies)[i].getW() >= xPos &&
       (*enemies)[i].getX() <= xPos + width &&
       (*enemies)[i].getY() + (*enemies)[i].getH() >= yPos &&
       (*enemies)[i].getY() <= yPos + height
     ) {
       // lastHit isn't set
       if(lastHit == 0) {
         lastHit = SDL_GetTicks();
       }
       // Only get hit every 80ms. Don't check if lastHit
       // hasn't been set
       if((lastHit != 0) && lastHit + 80 <= SDL_GetTicks()) {
         health--;
         lastHit = 0; // Reset lastHit
         return true;
       }
     }
  }

  return false;
  // Covert angle to radians
  // float ang = angle * PI / 180;
  // int tempX, tempY;
  // vector<pair<int, int>> coords = {};
  //
  // // Center
  // tempX = (0)*cos(ang) - (0)*sin(ang);
  // tempY = (0)*sin(ang) + (0)*cos(ang);
  // // Move the rotated positions relative to player
  // tempX += xPos + (width/2);
  // tempY += yPos + (height/2);
  //
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // Top right
  // // Start at 25, -25 (assuming player is 50x50) so center is at 0,0
  // tempX = (width/2)*cos(ang) - (-(height/2))*sin(ang);
  // tempY = (width/2)*sin(ang) + (-(height/2))*cos(ang);
  // // Move the rotated positions relative to player
  // tempX += xPos + (width/2);
  // tempY += yPos + (height/2);
  //
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // bottom right
  // // Start at 25, 25 (assuming player is 50x50) so center is at 0,0
  // tempX = (width/2)*cos(ang) - (height/2)*sin(ang);
  // tempY = (width/2)*sin(ang) + (height/2)*cos(ang);
  // // Move the rotated positions relative to player
  // tempX += xPos + (width/2);
  // tempY += yPos + (height/2);
  //
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // bottom left
  // // Start at -25, 25 (assuming player is 50x50) so center is at 0,0
  // tempX = (-(width/2))*cos(ang) - (height/2)*sin(ang);
  // tempY = (-(width/2))*sin(ang) + (height/2)*cos(ang);
  // // Move the rotated positions relative to player
  // tempX += xPos + (width/2);
  // tempY += yPos + (height/2);
  //
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // // Top left
  // // Start at -25, -25 (assuming player is 50x50) so center is at 0,0
  // tempX = (-(width/2))*cos(ang) - (-(height/2))*sin(ang);
  // tempY = (-(width/2))*sin(ang) + (-(height/2))*cos(ang);
  // // Move the rotated positions relative to player
  // tempX += xPos + (width/2);
  // tempY += yPos + (height/2);
  //
  // coords.push_back(pair<int,int>(tempX, tempY));
  //
  // SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
  // Draw vertices rects
  // for(int i = 0; i < coords.size(); i++) {
  //   SDL_Rect tempR = {coords[i].first, coords[i].second, 5, 5};
  //   SDL_RenderFillRect(graphics.getRenderer(), &tempR);
  // }
}

void Player::draw(Graphics &graphics, SDL_Rect cameraRect) {

  // Draw bullets before player
  for(int i = 0; i < bullets.size(); i++) {
    // Remove bullets from vector if off screen
    if(bullets[i].outOfBounds()) {
      bullets.erase(bullets.begin() + i);
    }
    bullets[i].update();
    bullets[i].draw(graphics);
  }

  SDL_Rect transRect = playerRect;
  transRect.x = playerRect.x - cameraRect.x;
  transRect.y = playerRect.y - cameraRect.y;

  int opposite = mouseY - yPos;
  int adjacent = mouseX - xPos;
  angle = atan2(opposite, adjacent) * 180 / PI;
  SDL_RenderCopyEx(graphics.getRenderer(), playerTex, NULL, &transRect, angle, NULL, SDL_FLIP_NONE);

  SDL_SetRenderDrawColor(graphics.getRenderer(), 20, 20, 20, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &maxHealthRect);

  SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 255, 0, 255);
  SDL_RenderFillRect(graphics.getRenderer(), &healthRect);

  // Draw perp rects
  // SDL_SetRenderDrawColor(graphics.getRenderer(), 125, 255, 200, 255);
  // for(int i = 0; i < coords.size(); i++) {
  //   pair<int,int> p1 = coords[i];
  //   pair<int,int> p2 = coords[i + 1 == coords.size() ? 0 : i + 1];
  //   int tempX = p1.first - p2.first;
  //   int tempY = p1.second - p2.second;
  //   pair<int,int> perpEdge = {-tempY + 100, tempX + 100};
  //   SDL_Rect tempR = {perpEdge.first, perpEdge.second, 5, 5};
  //   SDL_RenderFillRect(graphics.getRenderer(), &tempR);
  // }
}

void Player::clean() {
  SDL_DestroyTexture(playerTex);
  Mix_FreeChunk(doubleSpeedChunk);
  cout << "Cleaned up player..." << endl;
}
