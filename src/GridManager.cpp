#include "GridManager.h"

#include <functional>
#include <iomanip>
#include <iostream>

#include "Game.h"

const int START_X = 0;
const int START_Y = -1;
const int EXTRA_GRID_SPACE = 3;

GridManager::GridManager()
{
  rows = 0;
  width = 0;
  height = 0;
  columns = 0;
  grid = nullptr;
}

void GridManager::initialize(int windowWidth, int windowHeight)
{
  width = windowWidth;
  height = windowHeight;
  updateGridSize(width, height);
}

void GridManager::updateGridSize(int windowWidth, int windowHeight)
{
  // Important: We need to clear the grid before changing the width and
  // height of the grid. Otherwise, we will have a memory leak.
  clearGrid();
  width = windowWidth;
  height = windowHeight;
  int tileSize = Game::getSetting(TILE_SIZE);
  columns = (width / tileSize) + EXTRA_GRID_SPACE;
  rows = (height / (tileSize / 4)) + EXTRA_GRID_SPACE;
  generateGrid();
  populateGrid(START_X, START_Y);
  printGrid();
}

void GridManager::updateTileSize()
{
  updateGridSize(width, height);
}

void GridManager::generateGrid()
{
  grid = new int **[rows];
  for (int row = 0; row < rows; row++) {
    grid[row] = new int *[columns];
    for (int column = 0; column < columns; column++)
      if (!shouldSkipTile(row, column)) grid[row][column] = new int[2];
  }
}

void GridManager::clearGrid()
{
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++)
      if (!shouldSkipTile(row, column)) delete[] grid[row][column];
    delete[] grid[row];
  }
  delete[] grid;
}

void GridManager::populateGrid(int startX, int startY)
{
  // Holds the start coordinates of the current row
  // This will be used to calculate the position of each tile in the row
  int currentRowStartX = startX;
  int currentRowStartY = startY;

  for (int row = 0; row < rows; row++) {
    // For each row (except the first one) we need to calculate
    // the start coordinates before proceeding to the tile's
    // coordinates calculation. The start coordinates are
    // calculated based on the previous row start coordinates.
    // For even rows, the X keeps the same value, while the Y is
    // incremented by 1. For odd rows, the X is incremented by
    // 1, while the Y keeps the same value.
    if (row != 0) {
      if (row % 2 == 0) {
        startX = grid[row - 1][0][0];
        startY = grid[row - 1][0][1] + 1;
      } else {
        startX = grid[row - 1][0][0] + 1;
        startY = grid[row - 1][0][1];
      }
    }

    // To calculate the coordinates of each tile in the current
    // row we should start from the start coordinates of the
    // current row and then proceed to the next tile by
    // decrementing the X and incrementing the Y by it's
    // position on the current row (the column index).
    for (int column = 0; column < columns; column++) {
      if (!shouldSkipTile(row, column)) {
        grid[row][column][0] = startX - column;
        grid[row][column][1] = startY + column;
      }
    }
  }
}

void GridManager::printGrid()
{
  if (!Game::getSetting(SHOW_LOGS)) return;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++)
      if (!shouldSkipTile(i, j))
        std::cout << "[" << std::setw(3) << grid[i][j][0] << "," << std::setw(3) << grid[i][j][1] << "] ";
    std::cout << std::endl;
  }
}

bool GridManager::shouldSkipTile(int currentLine, int currentColumn)
{
  return currentLine % 2 == 0 && currentColumn == columns - 1;
}

void GridManager::forEachTile(std::function<void(int, int)> callback)
{
  for (int row = 0; row < rows; row++)
    for (int column = 0; column < columns; column++)
      if (!shouldSkipTile(row, column))
        callback(grid[row][column][0], grid[row][column][1]);
}