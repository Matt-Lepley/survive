#include "game.h"

int main(int argc, char* argv[]) {

  Game game;
  game.init();


  Mix_Music *gameMusic = Mix_LoadMUS("backgroundMusic.wav");

  Mix_PlayMusic(gameMusic, -1);

  while(game.isRunning()) {
    if(game.getGamestate() == GAMESTATES::StartMenu) {
      Mix_PauseMusic();
      game.startMenuLoop();
    }
    if(game.getGamestate() == GAMESTATES::Playing) {
      Mix_ResumeMusic();
      game.gameloop();
    }
  }

  game.clean();
  Mix_FreeMusic(gameMusic);
  return 0;
}
