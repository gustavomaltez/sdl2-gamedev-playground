#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "GridManager.h"
#include "PositionHelper.h"
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
  managers.gridManager->initialize(width, height);

  // Temp
  texture = IMG_LoadTexture(managers.sdlManager->renderer, "assets/blocks.png");
  texture_rect.x = 16 * 1;
  texture_rect.y = 16 * 0;
  texture_rect.w = 16;  // the width of the texture
  texture_rect.h = 17;  // the height of the texture
  // ---

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
    Game::settings.tileSize = value;
    managers.gridManager->updateTileSize();
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
    int spriteSize = Game::getSetting(TILE_SIZE);

    // Temp

    SDL_Rect rect;
    Coordinates cords = PositionHelper::getTileIsometricScreenCoordinates(x, y);
    rect.x = cords.x;
    rect.y = cords.y;
    rect.w = spriteSize;
    rect.h = spriteSize;

    SDL_RenderCopy(managers.sdlManager->renderer, texture, &texture_rect, &rect);

    Lines square = PositionHelper::getFullTileLines(rect.x, rect.y);
    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 100, 200, 255);
    SDL_RenderDrawLine(managers.sdlManager->renderer, square.top.x1, square.top.y1, square.top.x2, square.top.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, square.left.x1, square.left.y1, square.left.x2, square.left.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, square.bottom.x1, square.bottom.y1, square.bottom.x2, square.bottom.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, square.right.x1, square.right.y1, square.right.x2, square.right.y2);

    Lines surface = PositionHelper::getTileSurfaceLines(rect.x, rect.y);
    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 100, 50, 200, 255);
    SDL_RenderDrawLine(managers.sdlManager->renderer, surface.top.x1, surface.top.y1, surface.top.x2, surface.top.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, surface.left.x1, surface.left.y1, surface.left.x2, surface.left.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, surface.bottom.x1, surface.bottom.y1, surface.bottom.x2, surface.bottom.y2);
    SDL_RenderDrawLine(managers.sdlManager->renderer, surface.right.x1, surface.right.y1, surface.right.x2, surface.right.y2);
    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 0, 0, 255);
    // ---
  });

  SDL_RenderPresent(managers.sdlManager->renderer);
}
