#include "Game.h"
#include "SDLManager.h"
#include <SDL2/SDL.h>
#include <iostream>

void Game::initialize()
{
    std::cout << "Initializing Game" << std::endl;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    SDLManager sdlManager;

    running = true;

    while (running)
    {
        frameStart = SDL_GetTicks();

        handleEvents(&sdlManager);
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::handleEvents(SDLManager *sdlManager)
{
    SDL_Event event;

    while (sdlManager->handleEvents(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            std::cout << "Event handled" << std::endl;
            break;
        case SDL_QUIT:
            running = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                std::cout << "Window resized" << std::endl;
            }
            break;
        default:
            break;
        }
    }

    std::cout << "Game input handled" << std::endl;
}

void Game::update()
{
    std::cout << "Game updated" << std::endl;
}

void Game::render()
{
    std::cout << "Game rendered" << std::endl;
}
