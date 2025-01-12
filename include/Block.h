#pragma once

#include <vector>

// Possible block colors to be displayed on screen
// Each color has an ASCII code assigned so it can be displayed in terminal
enum class BlockColor
{
	NONE = ' ',
	RED = 'r',
	GREEN ='g',
	BLUE = 'b',
	YELLOW = 'y',
	CYAN = 'c',
	MAGENTA = 'm'
};

// Block position in 2D plane
using BlockPosition = struct { int x{}; int y{}; };

// Vector of block positions
using BlockPositionVector = std::vector<BlockPosition>;

// Matrix that contains block colors
// Each row and column can be represendted as 2D coordinates (BlockPosition)
// Used to create a game board
using BlockMatrix = std::vector<std::vector<BlockColor>>;
