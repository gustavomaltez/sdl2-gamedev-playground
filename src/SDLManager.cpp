#include "SDLManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

SDLManager::~SDLManager()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void SDLManager::initialize()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Error initializing SDL:" << SDL_GetError() << std::endl;
  }
  if (TTF_Init() != 0) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
  }
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cout << "Error initializing SDL_image" << IMG_GetError() << std::endl;
  }

  window = SDL_CreateWindow("Hyrdanya BETA", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), 400, 250, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, 0);
}

int SDLManager::handleEvents(SDL_Event *event)
{
  return SDL_PollEvent(event);
}