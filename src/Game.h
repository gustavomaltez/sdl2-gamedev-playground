#ifndef GAME_H
#define GAME_H

#include "GridManager.h"
#include "SDLManager.h"

struct Managers {
  SDLManager *sdlManager;
  GridManager *gridManager;
};

#define TILE_SIZE 0
#define SHOW_LOGS 1

struct Settings {
  int tileSize;
  bool showLogs;
};

struct State {
  bool isRunning;
};

class Game
{
 public:
  Managers managers;
  void initialize();
  void updateSetting(int setting, int value);
  static int getSetting(int setting);

 private:
  static Settings settings;
  State state;
  void handleEvents();
  void update();
  void render();
  // Temp
  SDL_Texture *texture;
  SDL_Rect texture_rect;
};

#endif /* GAME_H */