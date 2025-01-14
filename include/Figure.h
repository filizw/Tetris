#pragma once

#include "Block.h"

class Figure
{
public:
	/*
	* Default constructor
	*/
	Figure();

	/*
	* Constructor
	* 
	* INPUT: number of blocks that make up figure, color of figure
	*/
	Figure(unsigned int blockCount, BlockColor color);

	/*
	* Returns color of figure
	* 
	* OUTPUT: color of figure
	*/
	BlockColor getColor() const;

	/*
	* Returns positions of blocks that make up figure
	* 
	* OUTPUT: vector of block positions
	*/
	BlockPositionVector getBlockPositions() const;

	/*
	* Moves figure one position left
	* 
	* REMARKS: saves current positions before making a move
	*/
	void moveLeft();

	/*
	* Moves figure one position right
	*
	* REMARKS: saves current positions before making a move
	*/
	void moveRight();

	/*
	* Moves figure one position down
	*
	* REMARKS: saves current positions before making a move
	*/
	void moveDown();

	/*
	* Rotates figure by 90 degrees
	*
	* REMARKS: saves current positions before making a move
	*/
	void rotate();

	/*
	* Loads positions saved before making a move
	*/
	void loadPreviousBlockPositions();

protected:
	unsigned int blockCount{};
	BlockColor color{};
	BlockPositionVector blockPositions;		// Current block positions
	BlockPositionVector prevBlockPositions;	// Block postions saved before making a move
};

class IFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of figure
	* 
	* REMARKS: initializes block positions of the corresponding figure
	*/
	IFigure(BlockColor color);
};

class JFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	JFigure(BlockColor color);
};

class LFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	LFigure(BlockColor color);
};

class OFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	OFigure(BlockColor color);
};

class SFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	SFigure(BlockColor color);
};

class TFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	TFigure(BlockColor color);
};

class ZFigure :public Figure
{
public:
	/*
	* Constructor
	*
	* INPUT: color of the figure
	*
	* REMARKS: initializes block positions of the corresponding figure
	*/
	ZFigure(BlockColor color);
};
