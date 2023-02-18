#ifndef GAME_H
#define GAME_H

#include "SDLManager.h"
#include "GridManager.h"

struct Managers
{
    SDLManager *sdlManager;
    GridManager *gridManager;
};

class Game
{
public:
    Managers managers;
    void initialize();

private:
    void handleEvents();
    void update();
    void render();
    bool running;
};

#endif /* GAME_H */