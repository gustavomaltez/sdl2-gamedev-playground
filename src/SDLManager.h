#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include <SDL2/SDL.h>
class SDLManager
{
 public:
  ~SDLManager();
  SDL_Window *window;
  SDL_Renderer *renderer;
  int handleEvents(SDL_Event *event);
  void initialize();
};

#endif /* SDLMANAGER_H */