#include "pch.h"

#include "Tetris.h"
#include <algorithm>
#include <random>

// Helper function to check if two given BlockPositionsVectors are the same
static bool compareBlockPositions(const BlockPositionVector& pos1, const BlockPositionVector& pos2)
{
	if (pos1.size() != pos2.size())
		return false;

	for (int i{}; i < pos1.size(); i++)
		if (pos1[i].x != pos2[i].x || pos1[i].y != pos2[i].y)
			return false;

	return true;
}

// Helper function to generate random integers according to given parameters
static int generateRandomInt(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

// Helper function to return one of the seven possible figures
static Figure generateRandomFigure()
{
	Figure figure;
	auto color = BlockColor::RED;

	switch (generateRandomInt(0, 6))
	{
	case 0:
		figure = IFigure(color);
		break;
	case 1:
		figure = JFigure(color);
		break;
	case 2:
		figure = LFigure(color);
		break;
	case 3:
		figure = OFigure(color);
		break;
	case 4:
		figure = SFigure(color);
		break;
	case 5:
		figure = TFigure(color);
		break;
	case 6:
		figure = ZFigure(color);
		break;
	default:
		break;
	}

	return figure;
}

TEST(FigueTest, MoveLeft) {
	auto figure = generateRandomFigure(); // Create new figure

	auto step = generateRandomInt(1, 10); // Move figure by this value

	auto expectedPositions = figure.getBlockPositions();
	std::transform(expectedPositions.cbegin(), expectedPositions.cend(), expectedPositions.begin(),
		[step](auto pos) { pos.x -= step;  return pos; }); // Move block positions left


	for (auto i{step}; i > 0; i--)
		figure.moveLeft();

	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare
}

TEST(FigueTest, MoveRight) {
	auto figure = generateRandomFigure(); // Create new figure

	auto step = generateRandomInt(1, 10); // Move figure by this value

	auto expectedPositions = figure.getBlockPositions();
	std::transform(expectedPositions.cbegin(), expectedPositions.cend(), expectedPositions.begin(),
		[step](auto pos) { pos.x += step;  return pos; }); // Move block positions right


	for (auto i{ step }; i > 0; i--)
		figure.moveRight();

	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare
}

TEST(FigueTest, MoveDown) {
	auto figure = generateRandomFigure(); // Create new figure

	auto step = generateRandomInt(1, 10); // Move figure by this value

	auto expectedPositions = figure.getBlockPositions();
	std::transform(expectedPositions.cbegin(), expectedPositions.cend(), expectedPositions.begin(),
		[step](auto pos) { pos.y += step;  return pos; }); // Move block positions down


	for (auto i{ step }; i > 0; i--)
		figure.moveDown();

	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare
}

TEST(FigueTest, Rotate) {
	auto figure = OFigure(BlockColor::BLUE); // Create new figure

	auto expectedPositions = figure.getBlockPositions();
	// First rotation
	expectedPositions[0] = { 5,1 };
	expectedPositions[2] = { 5,2 };
	expectedPositions[3] = { 4,2 };


	figure.rotate();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	// Second rotation
	expectedPositions[0] = { 4,2 };
	expectedPositions[2] = { 3,2 };
	expectedPositions[3] = { 3,1 };


	figure.rotate();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	// Third rotation
	expectedPositions[0] = { 3,1 };
	expectedPositions[2] = { 3,0 };
	expectedPositions[3] = { 4,0 };


	figure.rotate();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	// Fourth rotation
	expectedPositions[0] = { 4,0 };
	expectedPositions[2] = { 5,0 };
	expectedPositions[3] = { 5,1 };


	figure.rotate();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare
}

TEST(FigueTest, LoadPreviousBlockPositions) {
	auto figure = generateRandomFigure(); // Create new figure

	auto expectedPositions = figure.getBlockPositions();

	figure.moveLeft();
	figure.loadPreviousBlockPositions();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	figure.moveRight();
	figure.loadPreviousBlockPositions();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	figure.moveDown();
	figure.loadPreviousBlockPositions();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare

	figure.rotate();
	figure.loadPreviousBlockPositions();
	EXPECT_TRUE(compareBlockPositions(expectedPositions, figure.getBlockPositions())); // Compare
}

// Helper function to check if given board is Empty
static bool isBoardEmpty(const Board& board)
{
	for (const auto& row : board.getBlockMatrix())
		for (const auto& color : row)
			if (color != BlockColor::NONE)
				return false;

	return true;
}

// Helper function to check if given figure is placed on given board
static bool isFigurePlacedOnBoard(const Board& board, const Figure& figure)
{
	for (const auto& pos : figure.getBlockPositions())
		if (board.getBlockColor(pos) == BlockColor::NONE)
			return false;

	return true;
}

TEST(BoardTest, PlaceRemoveFigure) {
	Board board(10, 20); // Create new 10x20 blocks board
	EXPECT_TRUE(isBoardEmpty(board)); // Check if board is empty

	auto figure = generateRandomFigure(); // Create new figure
	board.placeFigure(figure); // Place figure on board

	EXPECT_TRUE(isFigurePlacedOnBoard(board, figure));

	board.removeFigure(figure); // Remove figure from board

	EXPECT_FALSE(isFigurePlacedOnBoard(board, figure));
	EXPECT_TRUE(isBoardEmpty(board));
}

TEST(BoardTest, CheckCollisions) {
	Board board(10, 20); // Create new 10x20 blocks board

	// Create two figures
	auto figure = generateRandomFigure();
	auto nextFigure = generateRandomFigure();

	EXPECT_TRUE(isBoardEmpty(board));
	EXPECT_FALSE(board.checkCollisions(nextFigure)); // Check if collisions occur on empty board

	board.placeFigure(figure); // Place figure on board
	EXPECT_TRUE(isFigurePlacedOnBoard(board, figure));

	EXPECT_TRUE(board.checkCollisions(nextFigure)); // Check if collisions occur between two figures
}

#include <iostream>
TEST(BoardTest, ClearRow) {
	Board board(10, 20); // Create new 10x20 blocks board
	EXPECT_TRUE(isBoardEmpty(board)); // Check if board is empty

	auto figure = OFigure(BlockColor::BLUE); // Create new figure

	// Helper function to move figure left by given step
	auto moveFigureLeft = [&figure](int step) {
		for (auto i{ step }; i > 0; i--)
			figure.moveLeft();
	};

	// Helper function to move figure right by given step
	auto moveFigureRight = [&figure](int step) {
		for (auto i{ step }; i > 0; i--)
			figure.moveRight();
	};

	// Helper function to check if row is full of blocks
	auto isRowFull = [&board](int row) {
		for (const auto& color : board.getBlockMatrix()[row])
			if (color == BlockColor::NONE)
				return false;

		return true;
	};

	// Populate two highest rows with blocks
	moveFigureLeft(4);

	for (int i{}; i < 5; i++)
	{
		board.placeFigure(figure);
		moveFigureRight(2);
	}

	// Check if two highest rows are full
	EXPECT_TRUE(isRowFull(0));
	EXPECT_TRUE(isRowFull(1));

	// Clear row one and check if row zero moved down
	board.clearRow(1);
	EXPECT_FALSE(isRowFull(0));
	EXPECT_TRUE(isRowFull(1));

	board.clearRow(1);
	EXPECT_TRUE(isBoardEmpty(board));
}

TEST(TetrisTest, GameOver) {
	Tetris tetris; // Create new Tetris instance

	// Stack blocks on each other
	for (auto i{ 1000 }; i > 0; i--)
		tetris.moveDown(); // This method creates new figure each time collision occurs

	EXPECT_EQ(tetris.getScore(), 0); // Check if score is 0
	EXPECT_TRUE(tetris.isGameOver()); // Check if game is over
}
