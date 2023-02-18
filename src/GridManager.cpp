#include "GridManager.h"
#include <iostream>
#include <iomanip>

GridManager::GridManager()
{
    columns = 0;
    rows = 0;
    width = 0;
    height = 0;
    tileSize = 0;
    grid = nullptr;
}

void GridManager::updateGridSize(int windowWidth, int windowHeight)
{
    clearGrid();
    width = windowWidth;
    height = windowHeight;

    const int EXTRA_SPACE = 3;
    columns = (width / tileSize) + EXTRA_SPACE;
    rows = (height / (tileSize / 4)) + EXTRA_SPACE;
    generateGrid();
}

void GridManager::initialize(int windowWidth, int windowHeight, int tileSize)
{
    width = windowWidth;
    height = windowHeight;
    this->tileSize = tileSize;
    updateGridSize(width, height);
}

void GridManager::updateTileSize(int tileSize)
{
    this->tileSize = tileSize;
    updateGridSize(width, height);
}

void GridManager::generateGrid()
{
    // Create the new grid
    grid = new int **[rows];

    for (int i = 0; i < rows; i++)
    {
        grid[i] = new int *[columns];
        for (int j = 0; j < columns; j++)
        {
            if (i % 2 == 0 && j == columns - 1)
                continue; // Skip the last column of even lines (it's not needed)
            grid[i][j] = new int[2];
        }
    }

    // Populate the grid
    int startX = 0;
    int startY = 0;

    for (int i = 0; i < rows; i++)
    {
        // Calculate the start point
        if (i != 0)
        {
            if (i % 2 == 0) // Even
            {
                startX = grid[i - 1][0][0];
                startY = grid[i - 1][0][1] + 1;
            }
            else
            {
                startX = grid[i - 1][0][0] + 1;
                startY = grid[i - 1][0][1];
            }
        }

        grid[i][0][0] = startX;
        grid[i][0][1] = startY;

        for (int j = 0; j < columns; j++)
        {
            if (i % 2 == 0 && j == columns - 1)
                continue; // Skip the last column of even lines (it's not needed)
            grid[i][j][0] = startX - j;
            grid[i][j][1] = startY + j;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i % 2 == 0 && j == columns - 1)
                continue; // Skip the last column of even lines (it's not needed)
            std::cout << "[" << std::setw(3) << grid[i][j][0] << "," << std::setw(3) << grid[i][j][1] << "] ";
        }
        std::cout << std::endl;
    }
}

void GridManager::clearGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i % 2 == 0 && j == columns - 1)
                continue; // Skip the last column of even lines (it's not needed)
            delete[] grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}