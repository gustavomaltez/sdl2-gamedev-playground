#include "Game.h"
#include "SDLManager.h"
#include "GridManager.h"
#include <SDL2/SDL.h>
#include <iostream>

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

    running = true;

    while (running)
    {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Game::handleEvents()
{
    SDL_Event event;

    while (managers.sdlManager->handleEvents(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            std::cout << "Keydown Event" << std::endl;
            break;
        case SDL_QUIT:
            running = false;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                std::cout << "Window resized" << std::endl;
                std::cout << "New width: " << event.window.data1 << std::endl;
                std::cout << "New height: " << event.window.data2 << std::endl;
                managers.gridManager->updateGridSize(event.window.data1, event.window.data2);
            }
            break;
        default:
            break;
        }
    }

    // std::cout << "Game input handled" << std::endl;
}

void Game::update()
{
    // std::cout << "Game updated" << std::endl;
}

void Game::render()
{
    SDL_RenderClear(managers.sdlManager->renderer);
    SDL_SetRenderDrawColor(managers.sdlManager->renderer, 255, 100, 50, 255);

    for (int iA = 0; iA < managers.gridManager->rows; iA++)
    {
        for (int jA = 0; jA < managers.gridManager->columns; jA++)
        {

            // Skip the last column of even lines (it's not needed)
            if (iA % 2 == 0 && jA == managers.gridManager->columns - 1)
                continue;

            int spriteSize = managers.gridManager->tileSize;
            int i = managers.gridManager->grid[iA][jA][0];
            int j = managers.gridManager->grid[iA][jA][1];
            int half = spriteSize / 2;

            SDL_Rect rect;
            rect.x = ((j * spriteSize) - (i * spriteSize)) / 2;
            rect.y = ((j * spriteSize) + (i * spriteSize)) / 4;
            rect.w = spriteSize;
            rect.h = spriteSize;

            SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y);
            SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize * 0.5, rect.y, rect.x + spriteSize, rect.y + spriteSize * 0.25);
            SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5);
            SDL_RenderDrawLine(managers.sdlManager->renderer, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5, rect.x, rect.y + spriteSize * 0.25);
            SDL_SetRenderDrawColor(managers.sdlManager->renderer, 0, 0, 0, 255);
        }
    }

    SDL_RenderPresent(managers.sdlManager->renderer);
}
