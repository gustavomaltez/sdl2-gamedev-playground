#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include <SDL2/SDL.h>
class SDLManager
{
public:
    SDLManager();
    ~SDLManager();
    SDL_Window *window;
    SDL_Renderer *renderer;
    int handleEvents(SDL_Event *event);
};

#endif /* SDLMANAGER_H */