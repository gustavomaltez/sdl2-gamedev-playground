#ifndef POSITIONHELPER_H
#define POSITIONHELPER_H

#include <SDL2/SDL.h>

struct Coordinates {
  int x;
  int y;
};

struct Line {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct Lines {
  Line top;
  Line right;
  Line bottom;
  Line left;
};

class PositionHelper
{
 public:
  /**
   * Gets the isometric screen coordinates based on the actual cartesian coordinates.
   *
   * IMPORTANT: The input coordinates are the actual cartesian coordinates,
   * and the output coordinates are the isometric screen coordinates (where
   * the tile on the (x,y) coordinates should be rendered on the screen).
   *
   * @param x The x coordinate in cartesian plan.
   * @param y The y coordinate in cartesian plan.
   *
   * @return The isometric screen coordinates.
   */
  static Coordinates getTileIsometricScreenCoordinates(int x, int y);

  /**
   * For a given cartesian coordinate, gets a set of lines that wraps the tile.
   *
   * For example, if the input coordinates are (0, 0), and the tile size is 32x32,
   * the output lines will be:
   * top:  {x1: 0, y1: 0, x2: 32, y2: 0} - A to B
   * right: {x1: 32, y1: 0, x2: 32, y2: 32} - B to D
   * bottom: {x1: 32, y1: 32, x2: 0, y2: 32} - D to C
   * left: {x1: 0, y1: 32, x2: 0, y2: 0} - C to A
   *
   *   [A]#############[B]
   *    #               #
   *    #               #
   *    #               #
   *    #               #
   *    #               #
   *   [C]#############[D]
   *
   * @param x The x coordinate in cartesian plan.
   * @param y The y coordinate in cartesian plan.
   *
   * @return A set of lines that wraps the tile.
   */
  static Lines getFullTileLines(int x, int y);

  /**
   * For a given cartesian coordinate, gets a set of lines that wraps the tile surface.
   *
   * For example, if the input coordinates are (0, 0), and the tile size is 32x32,
   * the output lines will be:
   * top: {x1: 0, y1: 16, x2: 16, y2: 0} - D to A
   * right: {x1: 16, y1: 0, x2: 32, y2: 16} - A to B
   * bottom: {x1: 32, y1: 16, x2: 16, y2: 32} - B to C
   * left: {x1: 16, y1: 32, x2: 0, y2: 16} - C to D
   *
   * ######## A ########
   * #      *   *      #
   * #    *       *    #
   * #  D          B   #
   * #    *       *    #
   * #      *   *      #
   * ######## C ########
   *
   * @param x The x coordinate in cartesian plan.
   * @param y The y coordinate in cartesian plan.
   *
   * @return A set of lines that wraps the tile surface.
   */
  static Lines getTileSurfaceLines(int x, int y);
};

#endif /* POSITIONHELPER_H */
