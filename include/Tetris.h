#pragma once

#include "Board.h"
#include <random>
#include <array>

class Tetris
{
public:
	/*
	* Default constructor
	* 
	* REMARKS: creates new figure and places it on board
	*/
	Tetris();

	/*
	* Returns board
	* 
	* OUTPUT: reference to board
	*/
	const Board& getBoard() const;

	/*
	* Returns next figure
	* 
	* OUTPUT: reference to next figure
	*/
	const Figure& getNextFigure() const;

	/*
	* Returns score
	* 
	* OUTPUT: score
	*/
	unsigned int getScore() const;

	/*
	* Checks if game is over
	* 
	* OUTPUT: true if game is over, false otherwise
	*/
	bool isGameOver() const;

	/*
	* Moves currentFigure left if possible
	*/
	void moveLeft();

	/*
	* Moves currentFigure right if possible
	*/
	void moveRight();

	/*
	* Moves currentFigure down if possible
	* 
	* REMARKS: if collision occurs then checks if there are any rows to clear
	*/
	void moveDown();

	/*
	* Rotates currentFigure if possible
	*/
	void rotate();

private:
	static const unsigned int boardWidth{ 10 };
	static const unsigned int boardHeight{ 20 };

	Board board;
	Figure currentFigure;
	Figure nextFigure;
	unsigned int score{};
	bool gameOver{}; // Flag indicating if game is over

	/*
	* Creates randomly generated figure
	* 
	* REMARKS: assigns nextFigure to currentFigure and newly created figure to nextFigure, sets gameOver flag if new figure cannot be placed
	*/
	void createNewFigure();

	/*
	* Checks if any row can be cleared
	* 
	* REMARKS: increases score if row was cleared
	*/
	void checkRows();
};
