#include "game.h"

int main(int argc, char* argv[]) {

  Game game;
  game.init();

  while(game.isRunning()) {
    if(game.getGamestate() == GAMESTATES::StartMenu) {
      game.startMenuLoop();
    }
    if(game.getGamestate() == GAMESTATES::Playing) {
      game.gameloop();
    }
  }

  game.clean();
  return 0;
}
