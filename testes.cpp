// Create a simple c++ program

#include <iostream>
using namespace std;

int main()
{
    // Consider a isometric map with 64x64 sprites.
    // Well, visually, it's 32x64, but each sprite has 64x64 pixels.
    // So, if we have a 640x640 map, we will have 10 columns and 20 lines.
    // 20 lines because visually each sprite has only 32 pixels of height.
    // So, 640 (map height) / 32 (sprite height) = 20 (lines).

    int width = 320;
    int height = 320;
    int spriteHeight = 32;
    int spriteWidth = 64;

    int columnCount = 0;
    int lineCount = 0;

    if (width % spriteWidth == 0)
        columnCount = width / spriteWidth;
    else
        columnCount = (width / spriteWidth) + 1;

    if (height % spriteHeight == 0)
        lineCount = height / spriteHeight;
    else
        lineCount = (height / spriteHeight) + 1;

    columnCount = 7;
    //         .C0.  .C1.   .C2.   .C3.   .C4.   .C5.   .C6.
    // Line 0 [0,0] [-1,1] [-2,2] [-3,3] [-4,4] [-5,5] - EVEN
    // Line 1 [1,0] [0,1] [-1,2] [-2,3] [-3,4] [-4,5] [-5,6] - ODD

    // Line 2 [1,1] [0,2] [-1,3] [-2,4] [-3,5] [-4,6] - EVEN
    // Line 3 [2,1] [1,2] [0,3] [-1,4] [-2,5] [-3,6] [-4,7] - ODD

    // Line 4 [2,2] [1,3] [0,4] [-1,5] [-2,6] [-3,7]
    // Line 5 [3,2] [2,3] [1,4] [0,5] [-1,6] [-2,7] [-3,8]

    // Line 6 [3,3] [2,4] [1,5] [0,6] [-1,7] [-2,8]
    // Line 7 [4,3] [3,4] [2,5] [1,6] [0,7] [-1,8] [-2,9]

    // Given a start point (x,y), we can calculate the whole matrix
    // Before calculating the matrix, we need to know the start point
    // For each line the start point will be calculated as:
    // - For odd lines, the start point will be X = previous SPx + 1 and Y = previous SPy.
    // - For even lines, the start point will be X = previous SPx and Y = previous SPy + 1.
    // Given the start point, we can calculate all points in the line.
    // X = Previous X + 1 and Y = Previous Y - 1.

    int startX = -5;
    int startY = -5;

    int matrix[lineCount][columnCount][2];

    for (int i = 0; i < lineCount; i++)
    {
        // Calculate the start point
        if (i != 0)
        {
            if (i % 2 == 0) // Even
            {
                startX = matrix[i - 1][0][0];
                startY = matrix[i - 1][0][1] + 1;
            }
            else
            {
                startX = matrix[i - 1][0][0] + 1;
                startY = matrix[i - 1][0][1];
            }
        }

        matrix[i][0][0] = startX;
        matrix[i][0][1] = startY;

        for (int j = 0; j < columnCount; j++)
        {
            if (i % 2 == 0 && j == columnCount - 1)
                continue; // Skip the last column of even lines (it's not needed)
            matrix[i][j][0] = startX - j;
            matrix[i][j][1] = startY + j;
        }
    }

    for (int i = 0; i < lineCount; i++)
    {
        cout << "Line " << i << " ";
        for (int j = 0; j < columnCount; j++)
        {
            if (i % 2 == 0 && j == columnCount - 1)
                continue;
            cout << "[" << matrix[i][j][0] << "," << matrix[i][j][1] << "]";
        }
        cout << endl;
    }
    return 0;
}