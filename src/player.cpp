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

  // Set Rects
  playerRect = {xPos, yPos, width, height};
  healthRect = {xPos - (health / 2), yPos - 50, health, 10};
  maxHealthRect = {healthRect.x - 2, healthRect.y - 2, healthRect.w + 4, healthRect.h + 4};

  maxHealthRect.h = 34;

  for(int i = 0; i < timerRects.size(); i++) {
    timerRects[i].x = maxHealthRect.x;
    timerRects[i].y = maxHealthRect.y + (10 * (i+1));
    timerRects[i].w = 0;
    timerRects[i].h = 10;
  }

  playerSurface = IMG_Load("player.png");
  playerTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), playerSurface);
  SDL_FreeSurface(playerSurface);

  damageFromEnemyChunk = Mix_LoadWAV("damage.ogg");
  shotChunk = Mix_LoadWAV("shot.wav");

  cout << "done initializing player!" << endl;
}

void Player::destroyBullet(int index) {
  bullets[index].clean();
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

SDL_Rect *Player::getFreezeTimerRect() {
  return &timerRects[1];
}

vector<Bullet> Player::getBullets() {
  return bullets;
}

void Player::shoot(int mouseX, int mouseY, Graphics &graphics) {
  Bullet bull;
  int bullX = (xPos + width) - (width / 2);
  int bullY = (yPos + height) - (height / 2);
  int opposite = mouseY - bullY;
  int adjacent = mouseX  - bullX;
  float angle = atan2(opposite, adjacent) * 180 / PI;

  bull.init(bullX, bullY, angle, graphics);
  bullets.push_back(bull);

  Mix_PlayChannelTimed(-1, shotChunk, 0, 200);
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

       removeDuplicatePowerups(obj.getDropValue());
       Powerup pu;
       pu.init(obj.getDropValue());
       powerups.push_back(pu);

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

void Player::handlePowerups(vector<Enemy>* enemies) {
  for(int i = 0; i < powerups.size(); i++) {
    if(powerups[i].timeleft() == 0) {
      powerups[i].clean();
      if(powerups[i].getValue() == DROPS::DoubleSpeed) {
        cout << "Removing double speed" << endl;
        removeDoubleSpeed();
      }
      if(powerups[i].getValue() == DROPS::Freeze) {
        cout << "Unfreezing Enemies" << endl;
        unfreezeEnemies(enemies);
      }
      powerups.erase(powerups.begin() + i);
      int tempVal = 0;

      if(powerups[i].getValue() == 2) {
        tempVal = 1;
      }

      if(powerups[i].getValue() == 1) {
        tempVal = 99;
      }

      if(tempVal == 0 || tempVal == 1) {
        timerRects[tempVal].w = 0;
      }

    // If powerup is still active
    } else {
      int tempVal = 0;

      if(powerups[i].getValue() == 2) {
        tempVal = 1;
      }

      if(powerups[i].getValue() == 1) {
        tempVal = 99;
      }

      if(tempVal == 0 || tempVal == 1) {
        timerRects[tempVal].w = (float)powerups[i].timeleft() / (float)powerups[i].getTimerDuration() * 100;
      }

      if(powerups[i].getValue() == DROPS::DoubleSpeed) {
        giveDoubleSpeed();
      }
      if(powerups[i].getValue() == DROPS::Nuke) {
        cout << "NUKEEEE" << endl;
        nuke(enemies);
        powerups.erase(powerups.begin() + i);
      }
      if(powerups[i].getValue() == DROPS::Freeze) {
        freezeEnemies(enemies);
      }
    }
  }
}

void Player::freezeEnemies(vector<Enemy>* enemies) {
  for(int i = 0; i < enemies->size(); i++) {
    (*enemies)[i].setSpeed(0);
  }
}

void Player::unfreezeEnemies(vector<Enemy>* enemies) {
  for(int i = 0; i < enemies->size(); i++) {
    (*enemies)[i].setSpeed((*enemies)[i].getNormalSpeed());
  }
}

void Player::giveDoubleSpeed() {
  speed = baseSpeed * 2;
}

void Player::removeDoubleSpeed() {
  speed = baseSpeed;
}

void Player::nuke(vector<Enemy>* enemies) {
  for(int i = 0; i < enemies->size(); i++) {
    (*enemies)[i].clean();
  }
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

  for(int i = 0; i < timerRects.size(); i++) {
    timerRects[i].x = maxHealthRect.x + 2;
    timerRects[i].y = maxHealthRect.y + (10 * (i+1) + 2);
  }
}

void Player::enemyCollision(Graphics &graphics, vector<Enemy> *enemies) {
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
       // Only get hit every 500ms. Don't check if lastHit
       // hasn't been set
       if((lastHit != 0) && lastHit + 500 <= SDL_GetTicks()) {
         health -= 5;
         Mix_PlayChannelTimed(-1, damageFromEnemyChunk, 0, 1000);
         lastHit = 0; // Reset lastHit
       }
     }
  }
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
}

int Player::getHealth() {
  return health;
}

void Player::clean() {
  SDL_DestroyTexture(playerTex);
  Mix_FreeChunk(damageFromEnemyChunk);
  Mix_FreeChunk(shotChunk);
  cout << "Cleaned up player..." << endl;
}
