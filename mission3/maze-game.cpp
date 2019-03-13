#include <iostream>
#include <string>
#include <random>
#include "game-map-defs.h"
#include "game-map-defs.h"
#include "game-map-utils.h"


// Checks if user want so play
// Return true if user wants to play; false otherwise
bool doesUserWantsToPlay()
{
    bool rResult = false;

    std::cout << "Maze Game" << std::endl;

    while (true)
    {
        std::cout << "Do you want to play? (1 - yes, 0 - no):";

        std::string answer;
        std::cin >> answer;

        if ((answer == "1") || (answer == "0"))
        {
            rResult = (answer == "1");
            break;
        }

        std::cout << "Sorry, I did not understand." << std::endl;
    }

    return rResult;
}

void recursiveMazeGenerator() 
{

}
// Generates maze
// Parameters:
//       maze - reference to maze field that will be modified
//              (walls added, added character and exit)
void generateMaze(Map &prMaze)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            if ((row == 0) || (row == cMazeRows - 1) || (column == 0) || (column == cMazeColumns - 1))
            {
                prMaze[row][column] = cWallSymbol;
            }
            else
            {
                prMaze[row][column] = cEmptySymbol;
            }
        }
    }

    

    // Place character - always at positon 1,1
    prMaze[1][1] = cCharacterSymbol;

    std::random_device rd;
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> rowGenerator = std::uniform_int_distribution<int>(2, cMazeRows - 2);
    std::uniform_int_distribution<int> columnGenerator = std::uniform_int_distribution<int>(2, cMazeColumns - 2);
    prMaze[rowGenerator(mt)][columnGenerator(mt)] = cExitSymbol;

    std::uniform_int_distribution<int> keyRowGenerator = std::uniform_int_distribution<int>(2, cMazeRows - 2);
    std::uniform_int_distribution<int> keyColumnGenerator = std::uniform_int_distribution<int>(2, cMazeColumns - 2);
    prMaze[keyRowGenerator(mt)][keyColumnGenerator(mt)] = cKeySymbol;
}

bool isStepAvaliable(char charMovedOnto, bool isKeyFound) 
{
    if (charMovedOnto == cWallSymbol || (charMovedOnto == cExitSymbol && isKeyFound == false))
    {
        return false;
    }
    return true;
}


// Moves character according to given command and retuns eaten symbol (if any)
// Parameters:
//      row - character row position
//      column - character column position
//      command - test string with given command ("l" - left, "r" - right, "u" - up, "d" - down)
//      prMaze - reference to maze field; will be modified as a result of command execution
char moveAndGather(int row,
                   int column,
                   const std::string &command,
                   Map &prMaze,
                   bool isKeyFound)
{
    char rCharMovedOnto = cEmptySymbol;

    // Take character out from map
    prMaze[row][column] = cEmptySymbol;

    if (command == "a")
    {
        rCharMovedOnto = prMaze[row][column - 1];

        if (isStepAvaliable(rCharMovedOnto, isKeyFound))
        {
            column--;
        }
    }

    if (command == "d")
    {
        rCharMovedOnto = prMaze[row][column + 1];

        if (isStepAvaliable(rCharMovedOnto, isKeyFound))
        {
            column++;
        }
    }

    if (command == "w")
    {
        rCharMovedOnto = prMaze[row - 1][column];

        if (isStepAvaliable(rCharMovedOnto, isKeyFound))
        {
            row--;
        }
    }

    if (command == "s")
    {
        rCharMovedOnto = prMaze[row + 1][column];

        if (isStepAvaliable(rCharMovedOnto, isKeyFound))
        {
            row++;
        }
    }

    // Place character back with new position
    prMaze[row][column] = cCharacterSymbol;

    return rCharMovedOnto;
}

// Prints message to player.
// Parameters:
//      message - text message to player
void gameMessage(const std::string& message)
{
    std::cout << std::endl << message << std::endl << std::endl;
}



// Moves character and check if exit was found as a result of that move.
// Parameters:
//      prMaze - reference to maze field; will be modified while player moves.
bool moveCharacterAndCheckIfExitFound(Map &prMaze, bool & rKeyFound)
{
    bool rExitFound = false;


    int charRow = 1;
    int charColumn = 1;
    if (scanForChar(prMaze, cCharacterSymbol, charRow, charColumn))
    {
        std::cout << "Command (a - left, d - right, s - up, w - down):";
        std::string command;
        std::cin >> command;

        const char charMovedOnto = moveAndGather(charRow, charColumn, command, prMaze, rKeyFound);

        if (charMovedOnto == cWallSymbol)
        {
            gameMessage("Cannot move here!");
        }

        if (charMovedOnto == cKeySymbol) 
        {
            gameMessage("You had a key");
            rKeyFound = true;
        }

        if (charMovedOnto == cExitSymbol && rKeyFound)
        {
            gameMessage("Exit found!");
            rExitFound = true;
        }
    }
    else
    {
        gameMessage("Error: cannot find char!");
    }

    return rExitFound;
}

// Executes one round of the game
void playMazeGame()
{
    std::cout << "LETS START!" << std::endl;
    bool rKeyFound = false;
    Map maze;
    generateMaze(maze);
    
    do
    {
        drawMaze(maze);
    }
    while (!moveCharacterAndCheckIfExitFound(maze, rKeyFound));
}

int main()
{
    while (doesUserWantsToPlay())
    {
        playMazeGame();
    }
}
