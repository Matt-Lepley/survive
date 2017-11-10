#include "graphics.h"

void Graphics::init() {
  cout << "initializing..." << endl;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gameWindow, &gameRenderer);
}

SDL_Renderer *Graphics::getRenderer() {
  return gameRenderer;
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
  SDL_RenderClear(gameRenderer);
}

void Graphics::clean() {
  SDL_DestroyRenderer(gameRenderer);
  SDL_DestroyWindow(gameWindow);

  SDL_Quit();
  cout << "Cleaned up..." << endl;
}
