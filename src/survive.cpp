#include "game.h"

int main(int argc, char* argv[]) {

  Game game;
  game.init();

  while(game.isRunning()) {
    game.gameloop();
  }

  game.clean();
  return 0;
}
