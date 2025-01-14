#include "Figure.h"

Figure::Figure()
{

}

Figure::Figure(unsigned int blockCount, BlockColor color) : blockCount(blockCount), color(color), blockPositions(blockCount)
{

}

BlockColor Figure::getColor() const
{
	return color;
}

BlockPositionVector Figure::getBlockPositions() const
{
	return blockPositions;
}

void Figure::moveLeft()
{
	prevBlockPositions = blockPositions; // Save current positions

	for (auto& pos : blockPositions)
		pos.x--;
}

void Figure::moveRight()
{
	prevBlockPositions = blockPositions; // Save current positions

	for (auto& pos : blockPositions)
		pos.x++;
}

void Figure::moveDown()
{
	prevBlockPositions = blockPositions; // Save current positions

	for (auto& pos : blockPositions)
		pos.y++;
}

void Figure::rotate()
{
	prevBlockPositions = blockPositions; // Save current positions
	auto center = blockPositions[1];	 // Get central position

	for (char i{}; i < blockCount; i++)
	{
		blockPositions[i].x = center.x - prevBlockPositions[i].y + center.y;
		blockPositions[i].y = center.y + prevBlockPositions[i].x - center.x;
	}
}

void Figure::loadPreviousBlockPositions()
{
	blockPositions = prevBlockPositions;
}

IFigure::IFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 3,0 };
	blockPositions[1] = { 4,0 };
	blockPositions[2] = { 5,0 };
	blockPositions[3] = { 6,0 };

	prevBlockPositions = blockPositions;
}

JFigure::JFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 3,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 3,1 };
	blockPositions[3] = { 5,1 };

	prevBlockPositions = blockPositions;
}

LFigure::LFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 5,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 5,1 };
	blockPositions[3] = { 3,1 };

	prevBlockPositions = blockPositions;
}

OFigure::OFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 4,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 5,0 };
	blockPositions[3] = { 5,1 };

	prevBlockPositions = blockPositions;
}

SFigure::SFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 4,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 3,1 };
	blockPositions[3] = { 5,0 };

	prevBlockPositions = blockPositions;
}

TFigure::TFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 4,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 3,1 };
	blockPositions[3] = { 5,1 };

	prevBlockPositions = blockPositions;
}

ZFigure::ZFigure(BlockColor color) : Figure(4, color)
{
	blockPositions[0] = { 4,0 };
	blockPositions[1] = { 4,1 };
	blockPositions[2] = { 3,0 };
	blockPositions[3] = { 5,1 };

	prevBlockPositions = blockPositions;
}
