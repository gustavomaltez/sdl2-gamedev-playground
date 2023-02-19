#include "Game.h"

#include <SDL2/SDL.h>

#include <iostream>

#include "GridManager.h"
#include "SDLManager.h"

Settings Game::settings = {64, false};

void Game::initialize()
{
  std::cout << "Initializing Game" << std::endl;
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  managers.sdlManager = new SDLManager();
  managers.sdlManager->initialize();

  int width, height;
  SDL_GetWindowSize(managers.sdlManager->window, &width, &height);

  managers.gridManager = new GridManager();
  managers.gridManager->initialize(width, height, 64);

  state.isRunning = true;

  while (state.isRunning) {
    frameStart = SDL_GetTicks();

    handleEvents();
    update();
    render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
  }
}

void Game::updateSetting(int setting, int value)
{
  if (setting == TILE_SIZE) {
    managers.gridManager->updateTileSize(value);
    Game::settings.tileSize = value;
  } else if (setting == SHOW_LOGS)
    Game::settings.showLogs = value;
  else
    std::cout << "Invalid setting" << std::endl;
}

int Game::getSetting(int setting)
{
  if (setting == TILE_SIZE)
    return Game::settings.tileSize;
  else if (setting == SHOW_LOGS)
    return Game::settings.showLogs;
  else
    std::cout << "Invalid setting" << std::endl;
  return 0;
}

void Game::handleEvents()
{
  SDL_Event event;

  while (managers.sdlManager->handleEvents(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        std::cout << "Keydown Event" << std::endl;
        break;
      case SDL_QUIT:
        state.isRunning = false;
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
          managers.gridManager->updateGridSize(event.window.data1, event.window.data2);
        break;
      default:
        break;
    }
  }
}

void Game::update()
{
  // std::cout << "Game updated" << std::endl;
}

void Game::render()
{
  SDL_RenderClear(managers.sdlManager->renderer);
  SDL_SetRenderDrawColor(managers.sdlManager->renderer, 255, 100, 50, 255);

  managers.gridManager->forEachTile([this](int x, int y) {
    int spriteSize = managers.gridManager->tileSize;

    SDL_Rect rect;
    rect.x = ((y * spriteSize) - (x * spriteSize)) / 2;
    rect.y = ((y * spriteSize) + (x * spriteSize)) / 4;
    rect.w = spriteSize;
    rect.h = spriteSize;

    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y);
    SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize * 0.5, rect.y, rect.x + spriteSize, rect.y + spriteSize * 0.25);
    SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5);
    SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5, rect.x, rect.y + spriteSize * 0.25);
    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 0, 0, 255);
  });

  SDL_RenderPresent(managers.sdlManager->renderer);
}
