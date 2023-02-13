#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

void cartesianToIsometric(int x, int y, int &isoX, int &isoY)
{
    isoX = (x - y) / 2;
    isoY = (x + y) / 4;
}

void drawnText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, const char *text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argv, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), 1000, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    SDL_Event event;

    TTF_Init();
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/blocks.png");
    TTF_Font *font = TTF_OpenFont("assets/Gameplay.ttf", 12);

    // Line
    int line = 1;
    int column = 3;
    SDL_Rect texture_rect;
    texture_rect.x = 16 * (column - 1);
    texture_rect.y = 17 * (line - 1);
    texture_rect.w = 16; // the width of the texture
    texture_rect.h = 17; // the height of the texture

    SDL_Rect dest_rect;

    int windowWidth = 0;
    int windowHeight = 0;
    int startX = 0;
    int startY = 0;

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int spriteSize = 80;

    int columnCount = (windowWidth / spriteSize);
    int lineCount = (windowHeight / (spriteSize / 2)) * 2 - 1;

    int matrix[lineCount][columnCount][2];
    int startingY = 0;

    for (int currentLine = 0; currentLine < lineCount; currentLine++)
    {
        for (int currentColumn = 0; currentColumn < columnCount; currentColumn++)
        {

            if (currentLine == 0) // If it's the first line, then we need to start the values
            {
                matrix[currentLine][currentColumn][0] = currentColumn * -1;
                matrix[currentLine][currentColumn][1] = currentColumn;
            }
            else
            {
                // Calculate the X value
                if (currentLine % 2 == 0) // For even lines, the X value is the previous line X value + 1
                    matrix[currentLine][currentColumn][0] = matrix[currentLine - 1][currentColumn][0] + 1;
                else // For odd lines, the X value is the previous line X value
                    matrix[currentLine][currentColumn][0] = matrix[currentLine - 1][currentColumn][0];

                // Calculate the Y value
                if (currentColumn == 0) // The first column will dictate the Y value for the entire line
                {
                    startingY = currentLine - matrix[currentLine][currentColumn][0];
                    matrix[currentLine][currentColumn][1] = startingY;
                }
                else // The following columns will be the previous column Y value + 1
                {
                    matrix[currentLine][currentColumn][1] = matrix[currentLine][currentColumn - 1][1] + 1;
                }
            }
        }
    }

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    startY++;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    startY--;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    startX++;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    startX--;
                }
                std::cout << "line: " << line << " column: " << column << std::endl;
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 100, 50, 255);

        for (int iA = 0; iA < lineCount; iA++)
        {
            for (int jA = 0; jA < columnCount; jA++)
            {

                int i = matrix[iA][jA][0];
                int j = matrix[iA][jA][1];
                int half = spriteSize / 2;

                SDL_Rect rect;
                rect.x = startX + (j - 0) * spriteSize;
                rect.y = startY + (i - 0.5) * spriteSize;
                rect.w = spriteSize;
                rect.h = spriteSize;

                char text[100];
                sprintf(text, "%d,%d", i, j);

                cartesianToIsometric(rect.x, rect.y, rect.x, rect.y);
                SDL_RenderCopy(renderer, texture, &texture_rect, &rect);

                SDL_SetRenderDrawColor(renderer, 255, 100, 50, 255);
                SDL_RenderDrawLine(renderer, rect.x, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y);
                SDL_RenderDrawLine(renderer, rect.x + spriteSize * 0.5, rect.y, rect.x + spriteSize, rect.y + spriteSize * 0.25);
                SDL_RenderDrawLine(renderer, rect.x + spriteSize, rect.y + spriteSize * 0.25, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5);
                SDL_RenderDrawLine(renderer, rect.x + spriteSize * 0.5, rect.y + spriteSize * 0.5, rect.x, rect.y + spriteSize * 0.25);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                // Current position in cartesian

                drawnText(renderer, font, rect.x + spriteSize * 0.35, rect.y + 10, text, {255, 255, 255, 255});
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}