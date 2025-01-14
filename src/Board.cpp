#include "Board.h"

Board::Board(unsigned int width, unsigned int height) : width(width), height(height)
{
	blockMatrix = std::vector(height, std::vector(width, BlockColor::NONE)); // Make matrix empty of colors
}

unsigned int Board::getWidth() const
{
	return width;
}

unsigned int Board::getHeight() const
{
	return height;
}

BlockColor Board::getBlockColor(BlockPosition position) const
{
	if (position.x < width && position.y < height) // Check if given position is in bounds
		return blockMatrix[position.y][position.x];
	else
		return BlockColor::NONE;
}

const BlockMatrix& Board::getBlockMatrix() const
{
	return blockMatrix;
}

void Board::placeFigure(const Figure& figure)
{
	const auto& color = figure.getColor();

	for (const auto& pos : figure.getBlockPositions())
		placeBlock(pos, color);
}

void Board::removeFigure(const Figure& figure)
{
	for (const auto& pos : figure.getBlockPositions())
		placeBlock(pos, BlockColor::NONE);
}

bool Board::checkCollisions(Figure& figure) const
{
	for (auto& pos : figure.getBlockPositions())
	{
		// Check bounds and content of matrix at current position
		if (pos.y >= 0 && (pos.x < 0 || pos.x >= width || pos.y >= height || getBlockColor(pos) != BlockColor::NONE))
		{
			figure.loadPreviousBlockPositions(); // Load saved positions if collision occured
			return true;
		}
	}

	return false;
}

void Board::clearRow(unsigned int row)
{
	if (row < height) // Check if given position is in bounds
	{
		for (; row > 0; row--)
			blockMatrix[row] = blockMatrix[row - 1];

		for (auto& color : blockMatrix[0])
			color = BlockColor::NONE;
	}
}

void Board::placeBlock(BlockPosition position, BlockColor color)
{
	if (position.x < width && position.y < height) // Check if given position is in bounds
		blockMatrix[position.y][position.x] = color;
}
