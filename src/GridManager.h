#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

class GridManager
{
public:
    GridManager();
    int columns;
    int rows;
    int width;
    int height;
    int tileSize;
    int ***grid;
    void initialize(int windowWidth, int windowHeight, int tileSize);
    void updateGridSize(int windowWidth, int windowHeight);
    void updateTileSize(int tileSize);

private:
    void generateGrid();
    void clearGrid();
};

#endif /* GRIDMANAGER_H */
