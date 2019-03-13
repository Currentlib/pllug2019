#ifndef GAME_MAP_DEFS_H
#define GAME_MAP_DEFS_H
#include <array>

const int cMazeColumns = 12;
const int cMazeRows = 8;

const char cEmptySymbol = ' ';
const char cWallSymbol = 'X';
const char cCharacterSymbol = '@';
const char cExitSymbol = '#';

using Map = std::array<std::array<char, cMazeColumns>, cMazeRows>;

#endif