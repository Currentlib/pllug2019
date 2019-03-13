#include <iostream>
#include "game-map-defs.h"


// Draws maze onto screen
// Parameters:
//      maze - maze field to draw
void drawMaze(Map &maze)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            std::cout << maze[row][column];
        }

        std::cout << std::endl;
    }
}

// Searches given char on the given maze field,
// returns if found and filling row and column with coordinates
// Parameters:
//      maze - maze field where character will be serched
//      charToFind - char that should be found on maze field
//      prCharRow - reference to row variable for which will be assigned row position
//      prCharColumn - reference to column variable for which will be assigned column position
// Returns true if found; false otherwise.
bool scanForChar(Map &maze,
                 const char charToFind,
                 int &prCharRow,
                 int &prCharColumn)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            if (maze[row][column] == charToFind)
            {
                prCharRow = row;
                prCharColumn = column;
                return true;
            }
        }
    }

    return false;
}