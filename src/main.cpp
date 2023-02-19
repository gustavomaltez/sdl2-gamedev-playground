#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "Game.h"

// ToDo:
// - [X] Create a game class to take care of the game loop.
// - [X] Create an abstraction to initialize SDL.
// - [X] Create an abstraction to get the exact number of columns and rows.
// - [X] Create an abstraction to generate the matrix of tiles based on the number of columns and rows.
// - [X] Create an abstraction to handle window resizing.
// - [ ] Create an abstraction to convert the mouse position to a tile position and vice versa.
// - [X] Refactor all written code and add comments explaining crucial topics.
// - [X] Create static class to hold developer settings and debug mode.
// - [ ] Create an abstraction to get the block type in a given position (x, y).
// - [ ] Create an abstraction to load and retrieve the textures.
// - [ ] Create an abstraction to allow to write text on the screen.
// - [ ] Create an abstraction to handle mouse clicks (get the block position clicked).
// - [ ] Create an abstraction to control rendering map position from a base coordinate. (This will allow to move the map around the screen).
// - [ ] Create an abstraction to handle map scrolling (map should be scrollable within the virtual grid).
// - [ ] Create an abstraction to handle gird operations (check where a mouse position is in the grid, convert cartesian to isometric coordinates, etc).
// - [ ] Create an abstraction to handle map loading and saving.
// - [ ] Create an abstraction to handle map editing.
// - [ ] Create an abstraction to draw debug information on the grid (tile coord, lines around the tiles, etc).
// - [ ] Create an abstraction to handle coordinates extractions from a given position (x, y).

int main(int argv, char **args)
{
  Game game;
  game.initialize();
  return 0;
}