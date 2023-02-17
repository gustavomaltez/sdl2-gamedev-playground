#ifndef GAME_H
#define GAME_H

#include "SDLManager.h"
class Game
{
public:
    void initialize();

private:
    void handleEvents(SDLManager *sdlManager);
    void update();
    void render();
    bool running;
};

#endif /* GAME_H */