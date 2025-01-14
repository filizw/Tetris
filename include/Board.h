#pragma once

#include "Figure.h"

class Board
{
public:
	/*
	* Constructor
	* 
	* INPUT: width and height of board
	*/
	Board(unsigned int width, unsigned int height);

	/*
	* Returns width of board
	* 
	* OUTPUT: width
	*/
	unsigned int getWidth() const;

	/*
	* Returns height of board
	*
	* OUTPUT: height
	*/
	unsigned int getHeight() const;

	/*
	* Returns color of single cell
	*
	* INPUT: position of cell
	* 
	* OUTPUT: color of cell
	*/
	BlockColor getBlockColor(BlockPosition position) const;

	/*
	* Returns matrix containing block colors
	*
	* OUTPUT: block matrix
	*/
	const BlockMatrix& getBlockMatrix() const;

	/*
	* Places figure on board
	* 
	* INPUT: reference to figure object
	*/
	void placeFigure(const Figure& figure);

	/*
	* Removes figure from board
	*
	* INPUT: reference to figure object
	*/
	void removeFigure(const Figure& figure);

	/*
	* Checks collisions between board and given figure
	*
	* INPUT: reference to figure object
	* 
	* OUTPUT: true if collision occured, false otherwise
	*/
	bool checkCollisions(Figure& figure) const;

	/*
	* Clears single row of board
	*
	* INPUT: row to clear
	* 
	* REMARKS: moves down content of board above given row by one position
	*/
	void clearRow(unsigned int row);

private:
	unsigned int width{};
	unsigned int height{};
	BlockMatrix blockMatrix;

	/*
	* Places single block on board
	* 
	* INPUT: position and color of block
	*/
	void placeBlock(BlockPosition position, BlockColor color);
};
