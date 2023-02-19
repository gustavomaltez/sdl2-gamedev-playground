#include "PositionHelper.h"

#include "Game.h"

Coordinates PositionHelper::getTileIsometricScreenCoordinates(int x, int y)
{
  int tileSize = Game::getSetting(TILE_SIZE);

  Coordinates isometricCoordinatesOnScreen;
  int cartesianXonScreen = x * tileSize;
  int cartesianYonScreen = y * tileSize;

  // We need to divide by 2 because each tile X starts at the middle of the left neighbor tile.
  isometricCoordinatesOnScreen.x = (cartesianYonScreen - cartesianXonScreen) / 2;
  // Here we divide by 4 because each tile starts at the middle of the top neighbor tile.
  // But since the visible part of the tile has half of the height of the sprite
  // we need to divide by 2 again.
  isometricCoordinatesOnScreen.y = (cartesianXonScreen + cartesianYonScreen) / 4;
  return isometricCoordinatesOnScreen;
}

Lines PositionHelper::getFullTileLines(int x, int y)
{
  Lines lines;
  int tileSize = Game::getSetting(TILE_SIZE);
  int xPlusTileSize = x + tileSize;
  int yPlusTileSize = y + tileSize;

  lines.top.x1 = x;
  lines.top.y1 = y;
  lines.top.x2 = xPlusTileSize;
  lines.top.y2 = y;

  lines.right.x1 = xPlusTileSize;
  lines.right.y1 = y;
  lines.right.x2 = xPlusTileSize;
  lines.right.y2 = yPlusTileSize;

  lines.bottom.x1 = xPlusTileSize;
  lines.bottom.y1 = yPlusTileSize;
  lines.bottom.x2 = x;
  lines.bottom.y2 = yPlusTileSize;

  lines.left.x1 = x;
  lines.left.y1 = yPlusTileSize;
  lines.left.x2 = x;
  lines.left.y2 = y;

  return lines;
}

Lines PositionHelper::getTileSurfaceLines(int x, int y)
{
  int tileSize = Game::getSetting(TILE_SIZE);
  int tileWidth = tileSize;
  int halfTileWidth = tileWidth / 2;
  int tileHeight = tileSize / 2;
  int halfTileHeight = tileHeight / 2;

  Lines lines;

  lines.top.x1 = x;
  lines.top.y1 = y + halfTileHeight;
  lines.top.x2 = x + halfTileWidth;
  lines.top.y2 = y;

  lines.right.x1 = x + halfTileWidth;
  lines.right.y1 = y;
  lines.right.x2 = x + tileWidth;
  lines.right.y2 = y + halfTileHeight;

  lines.bottom.x1 = x + tileWidth;
  lines.bottom.y1 = y + halfTileHeight;
  lines.bottom.x2 = x + halfTileWidth;
  lines.bottom.y2 = y + tileHeight;

  lines.left.x1 = x + halfTileWidth;
  lines.left.y1 = y + tileHeight;
  lines.left.x2 = x;
  lines.left.y2 = y + halfTileHeight;

  return lines;
}