#ifndef GAME_H
#define GAME_H

#include "SDLManager.h"
#include "GridManager.h"

struct Managers
{
    SDLManager *sdlManager;
    GridManager *gridManager;
};

#define TILE_SIZE 0
#define SHOW_LOGS 1

struct Settings
{
    int tileSize;
    bool showLogs;
};

struct State
{
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
};

#endif /* GAME_H */