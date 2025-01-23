#include "Tetris.h"

Tetris::Tetris() : board(boardWidth, boardHeight)
{
	createNewFigure(); // Create currentFigure
	createNewFigure(); // Create nextFigure

	board.placeFigure(currentFigure);
}

const Board& Tetris::getBoard() const
{
	return board;
}

const Figure& Tetris::getNextFigure() const
{
	return nextFigure;
}

unsigned int Tetris::getScore() const
{
	return score;
}

bool Tetris::isGameOver() const
{
	return gameOver;
}

void Tetris::moveLeft()
{
	if (!gameOver)
	{
		board.removeFigure(currentFigure);
		currentFigure.moveLeft();
		board.checkCollisions(currentFigure);
		board.placeFigure(currentFigure);
	}
}

void Tetris::moveRight()
{
	if (!gameOver)
	{
		board.removeFigure(currentFigure);
		currentFigure.moveRight();
		board.checkCollisions(currentFigure);
		board.placeFigure(currentFigure);
	}
}

void Tetris::moveDown()
{
	if (!gameOver)
	{
		board.removeFigure(currentFigure);
		currentFigure.moveDown();
		auto collisionOccurred = board.checkCollisions(currentFigure);
		board.placeFigure(currentFigure);

		if (collisionOccurred) // Check rows if collision occured
		{
			checkRows();
			createNewFigure(); // Create new figure
			board.placeFigure(currentFigure);
		}
	}
}

void Tetris::rotate()
{
	if (!gameOver)
	{
		board.removeFigure(currentFigure);
		currentFigure.rotate();
		board.checkCollisions(currentFigure);
		board.placeFigure(currentFigure);
	}
}

void Tetris::createNewFigure()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static constexpr std::array<BlockColor, 6> colors = {
		BlockColor::RED,
		BlockColor::GREEN,
		BlockColor::BLUE,
		BlockColor::YELLOW,
		BlockColor::CYAN,
		BlockColor::MAGENTA
	};

	std::uniform_int_distribution<> colorDist(0, colors.size() - 1);
	std::uniform_int_distribution<> figureDist(0, 6);

	auto color = colors[colorDist(gen)]; // Generate random color

	currentFigure = nextFigure;
	if (board.checkCollisions(currentFigure))
		gameOver = true; // If collision occurs the set gameOver flag

	switch (figureDist(gen)) // Generate random figure
	{
	case 0:
		nextFigure = IFigure(color);
		break;
	case 1:
		nextFigure = JFigure(color);
		break;
	case 2:
		nextFigure = LFigure(color);
		break;
	case 3:
		nextFigure = OFigure(color);
		break;
	case 4:
		nextFigure = SFigure(color);
		break;
	case 5:
		nextFigure = TFigure(color);
		break;
	case 6:
		nextFigure = ZFigure(color);
		break;
	default:
		break;
	}
}

void Tetris::checkRows()
{
	auto& blockMatrix = board.getBlockMatrix();

	unsigned int rowCount{}; // Number of cleared rows

	for (unsigned int row{}; row < boardHeight; row++)
	{
		unsigned int blockCount{}; // Number of blocks in single row, must be 10 for row to be cleared

		for (auto& color : blockMatrix[row])
			if (color != BlockColor::NONE)
				blockCount++;

		if (blockCount == boardWidth)
		{
			board.clearRow(row);
			rowCount++;
		}
	}

	score += rowCount * rowCount; // Increase score
}
